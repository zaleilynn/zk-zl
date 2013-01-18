#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include <sstream>
#include <fstream>

#include "master/zk_master.h"
#include "master/cluster_manager.h"
#include "master/job.h"
#include "common/rpc.h"
#include "proxy/worker/gen-cpp/Worker.h"

using log4cplus::Logger;

using std::ifstream;
using std::stringstream;


static Logger logger = Logger::getInstance("master");

Job::Job(const JobInfo& job_info){
    m_info = job_info;
}

bool Job::SetJobStatus(const string& status){
    return ZKMasterI::Instance()->Set("/job/" + m_id + "/status", status); 
}

string Job::GetJobStatus(){
    string data;
    int32_t version;
    if(!ZKMasterI::Instance()->Get("/job/" + m_id + "/status", data, version) != false){
        LOG4CPLUS_ERROR(logger, "cannot get data from zk:" << "/job/" + m_id + "/status");
        return "";
    }
    return data;
    /*
    if("FAILED" == data || "FINISHED" == data || "WAITING" == data){
        return data;
    } else if ("HANDLING" == data) {
        vector<string> task_list;
        if(!ZKMasterI::Instance()->GetChildren("/job/" + m_id, task_list)){
            LOG4CPLUS_ERROR(logger, "cannot get data from zk:" << "/job/" + m_id);
            return ""; 
        }
        for(unsigned i = 0; i < task_list.size(); i++) {
            if(!ZKMasterI::Instance()->Get("/job/" + m_id + "/" + 
                                           task_list[i] + "/status", data, version)){
                LOG4CPLUS_ERROR(logger, "cannot get data from zk:" << "/job/" + m_id + "/" + task_list[i] + "/status");
                return "";
            }
        }
        if("FAILED" == data) {
            SetJobStatus("FAILED");
            return data;
        } 
    } else {
        LOG4CPLUS_ERROR(logger, "unknown state" << data);
        return "";
    }
    */
}

bool Job::Init(){
    string path = "/job";
    if(!ZKMasterI::Instance()->Create(path, "", ZOO_SEQUENCE)) {
        LOG4CPLUS_ERROR(logger, "cannot create new job");
        return false;
    }

    int32_t index = path.rfind("/");

    m_id = path.substr(index + 1);

    LOG4CPLUS_INFO(logger, "initialize new job " << m_id);

    path = "/job/" + m_id + "/status";
    if(ZKMasterI::Instance()->Create(path, "WAITING") == false) {
        LOG4CPLUS_ERROR(logger, "cannot create job status:" << m_id);
        return false;
    } 
    path = "/job/" + m_id + "/task";
    if(ZKMasterI::Instance()->Create(path) == false) {
        LOG4CPLUS_ERROR(logger, "cannot create job task:" << m_id);
        return false;
    }
    return true;
}

void Job::Do(){
    if(SetJobStatus("HANDLING") == false) {
        LOG4CPLUS_ERROR(logger, "cannot change job status to HANDLING:" << m_id);
        return;
    }

    //从部署虚拟机，到下装应用到虚拟机以及运行应用，收集应用运行结果，全部自动完成
    if(m_info.operate == "auto") {
        LOG4CPLUS_INFO(logger, "in doing auto job");
        string path = "/virtual_cluster";
        if(!ZKMasterI::Instance()->Create(path, "" , ZOO_SEQUENCE)) { 
            LOG4CPLUS_ERROR(logger, "cannot create new virtual cluster");
            if(SetJobStatus("FAILED") == false) {
                LOG4CPLUS_ERROR(logger, "cannot change job status to FAILED:" << m_id);
                return;
            }
            return;
        }

        string cluster_id = path.substr(path.rfind("/") + 1);

        LOG4CPLUS_INFO(logger, "creating new virtual cluster, id" << cluster_id);
        path = "/job/" + m_id + "/vc_num";
        //将这个job创造的vc cluster_id编号写入
        if(!ZKMasterI::Instance()->Create(path, cluster_id)){
            LOG4CPLUS_ERROR(logger, "cannot write virtual cluster num to job " << m_id);
            if(SetJobStatus("FAILED") == false) {
                LOG4CPLUS_ERROR(logger, "cannot change job status to FAILED:" << m_id);
                return;
            } 
            return;
        }
 
        ClassAd res;
        if(!res.InsertAttr("vcpu", m_info.os_info.vcpu) || 
           !res.InsertAttr("memory", m_info.os_info.memory)) {
            LOG4CPLUS_ERROR(logger, "cannot insert vcpu or memory into classad");
            if(SetJobStatus("FAILED") == false) {
                LOG4CPLUS_ERROR(logger, "cannot change job status to FAILED:" << m_id);
                return;
            }
            return; 
        }
  
        for(int32_t i = 0; i < m_info.instance ; i++) {
            //返回的machine代表在哪里物理机器上面分配了资源
            string machine = ClusterManagerI::Instance()->AllocateResource(res);
            if(machine.empty()) {
                LOG4CPLUS_ERROR(logger, "no enough resource for " << m_id);
                if(SetJobStatus("FAILED") == false) {
                    LOG4CPLUS_ERROR(logger, "cannot change job status to FAILED:" << m_id);
                    continue;
                }
                continue;
            }

            LOG4CPLUS_INFO(logger, "allocate reousce on " << machine);
            
            path = "/job/" + m_id + "/task"; 
            if(!ZKMasterI::Instance()->Create(path, "" , ZOO_SEQUENCE)) {
                LOG4CPLUS_ERROR(logger, "cannot create new job task");
                if(ClusterManagerI::Instance()->ReleaseResourceOnMachine(machine, res) == false){
                    LOG4CPLUS_ERROR(logger, "cannot release resource" << res << " on " << machine);
                }
                if(SetJobStatus("FAILED") == false) {
                    LOG4CPLUS_ERROR(logger, "cannot change job status to FAILED:" << m_id);
                }
                continue;
            }

            string task_path = path; 
            string task_id = task_path.substr(task_path.rfind("/") + 1);
            TaskInfo task_info;
            task_info.task_id = task_id;
            task_info.job_id = m_id;
            task_info.operate = m_info.operate;
            task_info.app_info= m_info.app_info;
            task_info.vm_info.type = "kvm";
       
            path += "/status";
            if(!ZKMasterI::Instance()->Create(path, "WAITING")) {
                LOG4CPLUS_ERROR(logger, "cannot create task status");
                if(ClusterManagerI::Instance()->ReleaseResourceOnMachine(machine, res) == false){
                    LOG4CPLUS_ERROR(logger, "cannot release resource" << res << " on " << machine);
                }
                if(SetJobStatus("FAILED") == false) {
                    LOG4CPLUS_ERROR(logger, "cannot change job status to FAILED:" << m_id);
                }
                continue;
            }
  
            string worker_endpoint = ClusterManagerI::Instance()->GetMachineRPCEndpoint(machine); 
            if(worker_endpoint.empty()){ 
                LOG4CPLUS_ERROR(logger, "cannot get worker endpoint:" << machine);
                if(ClusterManagerI::Instance()->ReleaseResourceOnMachine(machine, res) == false){
                    LOG4CPLUS_ERROR(logger, "cannot release resource" << res << " on " << machine);
                }
                if(SetJobStatus("FAILED") == false) {
                    LOG4CPLUS_ERROR(logger, "cannot change job status to FAILED:" << m_id);
                }
                continue;
            }          
  
            try {
                Proxy<WorkerClient> proxy = Rpc<WorkerClient, WorkerClient>::GetProxy(worker_endpoint);
                if(!proxy().StartTask(task_info)) {
                    LOG4CPLUS_ERROR(logger, "cannot start task on " << machine);  
                    if(ClusterManagerI::Instance()->ReleaseResourceOnMachine(machine, res) == false){
                        LOG4CPLUS_ERROR(logger, "cannot release resource" << res << " on " << machine);
                    }
            
                    if(SetJobStatus("FAILED") == false) {
                        LOG4CPLUS_ERROR(logger, "cannot change job status to FAILED:" << m_id);
                    }
                    continue;
                }
            }  catch (TException &tx) {
                LOG4CPLUS_ERROR(logger, "cannot start task on " << machine);
                if(ClusterManagerI::Instance()->ReleaseResourceOnMachine(machine, res) == false){
                    LOG4CPLUS_ERROR(logger, "cannot release resource" << res << " on " << machine);
                }
                if(SetJobStatus("FAILED") == false) {
                    LOG4CPLUS_ERROR(logger, "cannot change job status to FAILED:" << m_id);
                }
                continue;
            }
        } 
    }
    /*
    while(true) {  
    //监控子task状态的代码
        vector<string> task_list;
        string data;
        int32_t version;
        if(!ZKMasterI::Instance()->GetChildren("/job/" + m_id, task_list)){
            LOG4CPLUS_ERROR(logger, "cannot get data from zk:" << "/job/" + m_id);
            //这里需要考虑一下是不是退出
            break;
        }
        int32_t success_count;
        for(unsigned i = 0; i < task_list.size(); i++) {
            if(!ZKMasterI::Instance()->Get("/job/" + m_id + "/" + 
                                           task_list[i] + "/status", data, version)){
                LOG4CPLUS_ERROR(logger, "cannot get data from zk:" << "/job/" + m_id + "/" + task_list[i] + "/status");
                break;
            }
        }
        if("FAILED" == data) {
            if(!SetJobStatus("FAILED")) {
                LOG4CPLUS_ERROR(logger, "cannot change job status to FAILED:" << m_id); 
            }
            break;
        } else if("FINISHED" == data) {
            success_count++;
        }
    }
    */
    LOG4CPLUS_INFO(logger, "job " << m_id << " ends");
}
