#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "worker/worker_config.h"
#include "worker/resource_manager.h"
#include "worker/vm_manager.h"
#include "worker/zk_worker.h"
#include "common/rpc.h"
#include "worker/worker_service.h"

using log4cplus::Logger;
using log4cplus::ConsoleAppender;
using log4cplus::Appender;
using log4cplus::Layout;
using log4cplus::PatternLayout;
using log4cplus::helpers::SharedObjectPtr;
using std::string;
using std::auto_ptr;

int32_t main(int argc, char ** argv){
    SharedObjectPtr<Appender> append(new ConsoleAppender());
    append->setName(LOG4CPLUS_TEXT("append for worker"));
    auto_ptr<Layout> layout(new PatternLayout(LOG4CPLUS_TEXT("%d{%m/%d/%y %H:%M:%S} %p %l:%m %n")));
    append->setLayout(layout);
    Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("worker"));
    logger.addAppender(append);
    logger.setLogLevel(log4cplus::DEBUG_LOG_LEVEL);
    //logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);

    char *p = getenv("ZLYNN_HOME");
    if( NULL == p) {
        LOG4CPLUS_ERROR(logger, "ZLYNN_HOME is not set");
        exit(1);
    }
 
    string zlynn_home(p);
    if(!WorkerConfigI::Instance()->Init(zlynn_home + "/conf/worker.xml")) {
        LOG4CPLUS_ERROR(logger, "error in reading worker config");
        exit(1);
    }

    if(access("/var/lib/zlynn", F_OK) == -1) {
       if(mkdir("/var/lib/zlynn",0755) != 0){
           LOG4CPLUS_ERROR(logger, "error in creating zlynn work dir");
           exit(1);
       }
    }
    if(!ZKWorkerI::Instance()->Init()){
        LOG4CPLUS_ERROR(logger, "cannot initialize zk worker");
        exit(1);
    }

    if(!ResourceManagerI::Instance()->Init()) { 
        LOG4CPLUS_ERROR(logger, "cannot initialize resource manager");
        exit(1);
    }

    if(!VMManagerI::Instance()->Init(zlynn_home + "/conf/vm.xml")) {
        LOG4CPLUS_ERROR(logger, "cannot initialize vm manager");
        exit(1);
    }
  
    int32_t rpc_port = atoi(WorkerConfigI::Instance()->Get("rpc_port").c_str());
    if(rpc_port == 0) {
        LOG4CPLUS_ERROR(logger, "error in rpc_port");
        exit(-1);
    }

    Rpc<WorkerService, WorkerProcessor>::Listen(rpc_port);
}
