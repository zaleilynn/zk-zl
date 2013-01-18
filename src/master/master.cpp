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
#include <boost/thread.hpp>

#include "master/master_config.h"
//zk_master必须在最上面，不知道是个什么bug
#include "master/zk_master.h"
#include "common/rpc.h"
#include "master/master_service.h"

using log4cplus::Logger;
using log4cplus::ConsoleAppender;
using log4cplus::Appender;
using log4cplus::Layout;
using log4cplus::PatternLayout;
using log4cplus::helpers::SharedObjectPtr;
using std::string;
using std::auto_ptr;

extern void* JobProcessor();

int32_t main(int argc, char ** argv){
    SharedObjectPtr<Appender> append(new ConsoleAppender());
    append->setName(LOG4CPLUS_TEXT("append for master"));
    auto_ptr<Layout> layout(new PatternLayout(LOG4CPLUS_TEXT("%d{%m/%d/%y %H:%M:%S} %p %l:%m %n")));
    append->setLayout(layout); 
    Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("master"));
    logger.addAppender(append);
    //for debug
    logger.setLogLevel(log4cplus::DEBUG_LOG_LEVEL);
    //for normal use
    //logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);

    char *p = getenv("ZLYNN_HOME");
    if( NULL == p) {
        LOG4CPLUS_ERROR(logger, "ZLYNN_HOME is not set");
        exit(1);
    }

    string zlynn_home(p);
    if(!MasterConfigI::Instance()->Init(zlynn_home + "/conf/master.xml")) { 
        LOG4CPLUS_ERROR(logger, "error in reading master config");
        exit(1);
    }

    if(access("/var/lib/zlynn", F_OK) == -1) {
       if(mkdir("/var/lib/zlynn",0755) != 0){
           LOG4CPLUS_ERROR(logger, "error in creating zlynn work dir");
           exit(1);
       }
    }

    if(!ZKMasterI::Instance()->Init()){
        LOG4CPLUS_ERROR(logger, "cannot initialize zk master");
        exit(1);
    }

    int32_t rpc_port = atoi(MasterConfigI::Instance()->Get("rpc_port").c_str());
    if(rpc_port == 0) {
        LOG4CPLUS_ERROR(logger, "error in rpc_port");
        exit(-1);
    }

    boost::thread job_processor_t(JobProcessor);

    Rpc<MasterService, MasterProcessor>::Listen(rpc_port);
    return 0;
}
