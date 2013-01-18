#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <boost/algorithm/string.hpp>

#include "master/zk_master.h"
#include "master/cluster_manager.h"
#include <iostream>
#include <sstream>

using log4cplus::Logger;
using boost::split;
using boost::is_any_of;
using std::stringstream;

static Logger logger = Logger::getInstance("master");

bool ClusterManager::AllocateResourceOnMachine(const string& machine, const ClassAd& resource) {
    string data;
    int32_t version;
    if(!ZKMasterI::Instance()->Get("/cluster" + machine + "/status", data, version)){
         return false;
    }

    if(data != "ONLINE") {
        return false;
    }

    if(!ZKMasterI::Instance()->Get("/cluster" + machine + "/resource", data, version)){
        return false;
    }   

    ClassAdParser parser;
    ClassAd* classad_ptr = parser.ParseClassAd(data);  
 
    //
    int32_t total_vcpu, total_memory, requried_vcpu, required_memory;
    if(!classad_ptr->EvaluateAttrInt("memory", total_memory) ||
       !classad_ptr->EvaluateAttrInt("vcpu", total_vcpu) ||
       !resource.EvaluateAttrInt("memory", required_memory) ||
       !resource.EvaluateAttrInt("vcpu", requried_vcpu)) {
        return false;    
    }

    //资源不够
    if( total_vcpu < requried_vcpu || total_memory < required_memory) {
        return false;
    }
   
    stringstream ss; 
    ss << "[ vcpu = " << total_vcpu - requried_vcpu << "; memory = " << total_memory - required_memory << " ]";
 
    if(!ZKMasterI::Instance()->Set("/cluster" + machine + "/resource", ss.str(), version)){
        return false;
    }
    return true;
}

string ClusterManager::AllocateResource(const ClassAd& resource){
    vector<string> machine_list;
    if(!ZKMasterI::Instance()->GetChildren("/cluster", machine_list)) {
        LOG4CPLUS_ERROR(logger, "cannot get machine_list");
        return "";
    }
    for(unsigned i = 0; i < machine_list.size(); i++) {
        //简单的从first fit算法
        if(AllocateResourceOnMachine(machine_list[i], resource) == true) {
            return machine_list[i];  
        }
    } 
    return "";
}

bool ClusterManager::ReleaseResourceOnMachine(const string& machine, const ClassAd& resource){
    string data;
    int32_t version;
    if(!ZKMasterI::Instance()->Get("/cluster" + machine + "/status", data, version)){
         return false;
    }
    if(data != "ONLINE") {
        return false;
    }
    if(!ZKMasterI::Instance()->Get("/cluster" + machine + "/resource", data, version)){
        return false;
    }

    ClassAdParser parser;
    ClassAd* classad_ptr = parser.ParseClassAd(data);

    //
    int32_t total_vcpu, total_memory, requried_vcpu, required_memory;
    if(!classad_ptr->EvaluateAttrInt("memory", total_memory) ||
       !classad_ptr->EvaluateAttrInt("vcpu", total_vcpu) ||
       !resource.EvaluateAttrInt("memory", required_memory) ||
       !resource.EvaluateAttrInt("vcpu", requried_vcpu)) {
        return false;
    }
   
    stringstream ss;
    ss << "[ vcpu = " << total_vcpu + requried_vcpu << "; memory = " << total_memory + required_memory << " ]"; 
    
    if(!ZKMasterI::Instance()->Set("/cluster" + machine + "/resource", ss.str(), version)){
        return false;
    }
    return true; 
}

string ClusterManager::GetMachineRPCEndpoint(const string& machine){
    string data;
    int32_t version;
    if(!ZKMasterI::Instance()->Get("/cluster" + machine + "/rpc_port", data, version)){
         return "";
    }
    return machine + ":" + data; 
}
