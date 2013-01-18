#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <sstream>

#include "worker/resource_manager.h"
#include "worker/worker_config.h"
#include "worker/zk_worker.h"
#include "common/system.h"

using log4cplus::Logger;
using std::stringstream;

static Logger logger = Logger::getInstance("master");

ResourceManager::~ResourceManager(){       
    if(ZKWorkerI::Instance()->Delete("/cluster/" + m_communication_ip) 
    == false) {
        LOG4CPLUS_ERROR(logger, "cannot delete machine");    
    } 
}

bool ResourceManager::Init(){
    string c_i = WorkerConfigI::Instance()->Get("communication_interface");
    if(c_i.empty()){
        LOG4CPLUS_ERROR(logger, "cannot find communication_interface");
        return false;
    }
    m_communication_ip = System::GetIP(c_i);
    if(m_communication_ip.empty()){
        LOG4CPLUS_ERROR(logger, "cannot get communication ip");
        return false;
    }

    string b_i = WorkerConfigI::Instance()->Get("bridge_interface");
    if(b_i.empty()){
        LOG4CPLUS_ERROR(logger, "cannot find bridge_interface");
        return false;
    }
    m_bridge_ip = System::GetIP(b_i);
    if(m_bridge_ip.empty()){
        LOG4CPLUS_ERROR(logger, "cannot get bridge ip");
        return false;
    }

    m_rpc_port = WorkerConfigI::Instance()->Get("rpc_port");
    //vcpu个数为CPU核数*8
    m_total_vcpu = System::CpuNum() * 8;
    m_total_memory = System::TotalMemory();

    string path;
    if(ZKWorkerI::Instance()->IsExists("/cluster/" + m_communication_ip) == false) {
        path = "/cluster/" + m_communication_ip;
        if(ZKWorkerI::Instance()->Create(path) == false){
            LOG4CPLUS_ERROR(logger, "cannot create machine to zk:" << m_communication_ip);
            return false;
        }
    }   

    if(ZKWorkerI::Instance()->IsExists("/cluster/" + m_communication_ip + "/vm") == false) {
        path = "/cluster/" + m_communication_ip + "/vm"; 
        if(ZKWorkerI::Instance()->Create(path) == false){
            LOG4CPLUS_ERROR(logger, "cannot create vm to zk:" << m_communication_ip);
            return false;
        }
    }
   
    path = "/cluster/" + m_communication_ip + "/status"; 
    if(ZKWorkerI::Instance()->Create(path, "ONLINE", ZOO_EPHEMERAL) == false) {
        LOG4CPLUS_ERROR(logger, "cannot write machine status to zk:" << m_communication_ip);
        return false;
    }

    //这里不分析就不用classad了，太麻烦了，而且worker多一个连接库  
    stringstream ss;
    ss << "[ vcpu = " << m_total_vcpu << "; memory = " << m_total_memory << " ]";
    string res = ss.str();
 
    if(ZKWorkerI::Instance()->Create(path, res, ZOO_EPHEMERAL) == false) {
        LOG4CPLUS_ERROR(logger, "cannot write resource to zk:" << m_communication_ip);
        return false;
    }

    ss.clear();
    ss.str("");
    ss << m_rpc_port;
    path = "/cluster/" + m_communication_ip + "/rpc_port";
    if(ZKWorkerI::Instance()->Create(path, ss.str(), ZOO_EPHEMERAL) == false) {
        LOG4CPLUS_ERROR(logger, "cannot write rpc port to zk:" << m_communication_ip);
        return false;
    }
    return true;
}

string ResourceManager::GetCommunicationIp(){
    return m_communication_ip;
}
