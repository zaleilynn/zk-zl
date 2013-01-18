#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

//这个必须放第一个...
#include "master/zk_master.h"
#include "master/master_service.h"

using log4cplus::Logger;

static Logger logger = Logger::getInstance("master");

void MasterService::SubmitJob(string& job_id, const JobInfo& job_info){

}

