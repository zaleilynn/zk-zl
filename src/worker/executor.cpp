#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "worker/zk_worker.h"
#include "worker/executor.h"

Executor::Executor(const TaskInfo& task_info) {
    m_info = task_info;
}

bool Executor::SetExecutorStatus(const string& status){
    return ZKWorkerI::Instance()->Set("/job/" + m_info.job_id + "/" 
                    + m_info.task_id + "/status", status);
}

string Executor::GetExecutorStatus() {
    string rtn;
    int32_t version; 
    if(!ZKWorkerI::Instance()->Get("/job/" + m_info.job_id + "/" 
                    + m_info.task_id + "/status", rtn, version)){
        return "";
    }
    return rtn;                       
}

bool Executor::Init(){
    return true;
}

void Executor::Do(){
    SetExecutorStatus("HANDLING");
    SetExecutorStatus("FINISHED");
}
