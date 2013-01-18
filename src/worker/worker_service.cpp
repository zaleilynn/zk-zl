#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

//这个必须放第一个...
#include "worker/zk_worker.h"
#include "worker/worker_service.h"
#include "worker/executor.h"

using log4cplus::Logger;

static Logger logger = Logger::getInstance("master");

bool WorkerService::StartTask(const TaskInfo& task_info){ 
    LOG4CPLUS_INFO(logger, "receive task" << task_info.task_id);
    ExecutorPtr executor(new Executor(task_info));
    if( NULL != executor) { 
        if(!executor->Init()) {
            LOG4CPLUS_ERROR(logger, "cannot init task");
            return false;
        }
        ExecutorBufferI::Instance()->PushBack(executor);
        LOG4CPLUS_INFO(logger, "push the executor into executor buffer");
    }
    return true;
}
