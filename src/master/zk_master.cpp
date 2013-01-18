#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include "master/zk_master.h"
#include "master/master_config.h"

using log4cplus::Logger;

static Logger logger = Logger::getInstance("worker");

bool ZKMaster::Init(){
    string zk_endpoint = MasterConfigI::Instance()->Get("zk_endpoint");

    if(zk_endpoint.empty()) {
        LOG4CPLUS_ERROR(logger, "cannot get zk endpoint");
        return false;
    }

    zoo_set_debug_level(ZOO_LOG_LEVEL_ERROR);

    //10000是建立seesion的timeout，可以一直用的
    //heartbeat的时间是10000/3 = 3.3s
    m_zh = zookeeper_init(zk_endpoint.c_str(), DummyWatcher, 10000, 0, 0, 0);

    if(!m_zh) {
        LOG4CPLUS_ERROR(logger, "cannot initialize zookeeper,errno:" << errno); 
        return false;
    }

    char buf[512];  
 
    int32_t rc = zoo_exists(m_zh, "/job", 0, NULL);
    if(ZOK != rc) {
        rc = zoo_create(m_zh, "/job", NULL, -1,
                            &ZOO_OPEN_ACL_UNSAFE,0,
                            buf, sizeof(buf) - 1);
        if(ZOK != rc){
            LOG4CPLUS_ERROR(logger, "cannot create /job");
            return false;
        }
    } 

    rc = zoo_exists(m_zh, "/job/count", 0, NULL);
    if(ZOK != rc) {
        rc = zoo_create(m_zh, "/job/count", "1", 1,
                            &ZOO_OPEN_ACL_UNSAFE,0,
                            buf, sizeof(buf) - 1);
        if(ZOK != rc){
            LOG4CPLUS_ERROR(logger, "cannot create /job/count");
            return false;
        }
    }

    rc = zoo_exists(m_zh, "/virtual_cluster", 0, NULL);
    if(ZOK != rc) {
        rc = zoo_create(m_zh, "/virtual_cluster", NULL, -1,
                            &ZOO_OPEN_ACL_UNSAFE,0,
                            buf, sizeof(buf) - 1);
        if(ZOK != rc){
            LOG4CPLUS_ERROR(logger, "cannot create /virtual_cluster");
            return false;
        }
    }
    
    rc = zoo_exists(m_zh, "/virtual_cluster/count", 0, NULL);
    if(ZOK != rc) {
        rc = zoo_create(m_zh, "/virtual_cluster/count", "1", 1,
                            &ZOO_OPEN_ACL_UNSAFE,0,
                            buf, sizeof(buf) - 1);
        if(ZOK != rc){
            LOG4CPLUS_ERROR(logger, "cannot create /virtual_cluster/count");
            return false;
        }
    }
    return true;
}
