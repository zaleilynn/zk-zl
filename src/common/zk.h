#ifndef ZLYNN_SRC_COMMON_ZK_H_
#define ZLYNN_SRC_COMMON_ZK_H_

#include <zookeeper/zookeeper.h>
#include <string>
#include <vector>
#include <errno.h>
#include "common/constants.h"

using std::string;
using std::vector;

class ZK {
public:
    ZK(){
        m_zh = NULL;
    }

    ~ZK(){
        if(m_zh != NULL) {
            zookeeper_close(m_zh);
        }
    }

    virtual bool Init() = 0;

    //默认是固定节点,内不存储content
    //当创建节点的类型为sequential时候，path也负责返回新创建的节点值
    bool Create(string& path, const string& value = "", int32_t flags = 0) {
        char buf[512];
        int32_t rc;
        if (value.empty()) {
            rc = zoo_create(m_zh, path.c_str(), NULL, -1,
                                &ZOO_OPEN_ACL_UNSAFE,flags,
                                buf, sizeof(buf) - 1);
        } else {
            if(value.length() > MAX_ZNODE_VALUE_LENGTH) {
                return false;
            }
            rc = zoo_create(m_zh, path.c_str(), value.c_str(), value.length(),
                                &ZOO_OPEN_ACL_UNSAFE,flags,
                                buf, sizeof(buf) - 1);
            //顺带返回值
            path = buf; 
        }
        
        if(ZOK != rc){
            return false;
        }
        return true;
    }

    bool IsExists(const string& path) {
        int32_t rc = zoo_exists(m_zh, path.c_str(), 0, NULL);
        if(ZOK == rc){
            return true;
        }
        return false;
    }

    bool Set(const string& path, const string& value, int32_t version = -1){
        int32_t rc;
        if(value.empty()) {
            rc = zoo_set(m_zh, path.c_str(), NULL, -1, -1);
        } else {
            if(value.length() > MAX_ZNODE_VALUE_LENGTH) {
                return false;
            }
            rc = zoo_set(m_zh, path.c_str(), value.c_str(), value.length(), version);
        }
        if(ZOK != rc) {
            return false;
        }
        return true;
    }

    bool Delete(const string& path, int32_t version = -1) { 
        int32_t rc = zoo_delete(m_zh, path.c_str(), version);
        if(ZOK != rc) {
             return false;
        }
        return true;
    }

    bool GetChildren(const string& path, vector<string>& rtn) {
        String_vector children;
        int32_t rc = zoo_get_children(m_zh, path.c_str(), 0, &children);
        if(ZOK != rc){ 
             return false; 
        }
        for(int32_t i = 0; i < children.count; i++) {
             rtn.push_back(children.data[i]);
        }
        //需要不需要析构
        deallocate_String_vector(&children);
        return true; 
    }

    bool Get(const string& path, string& rtn, int32_t& version){
        //其实可以不用限制，先用zoo_exist获得长度即可
        //这里为了效率限制一下吧
        char buf[MAX_ZNODE_VALUE_LENGTH];
        int32_t buflen = sizeof(buffer);
        struct Stat stat;
        int32_t rc = zoo_get(m_zh, path.c_str(), 0, buf, &buflen, &stat);
        if(ZOK != rc) {
            rtn = "";
            version = -1;
            return false;
        }
        buf[buflen] = '\0';
        rtn = buf;
        version = stat.version;
        return true;
    }

protected:
    static void DummyWatcher(zhandle_t *zzh, int32_t type, int32_t state, const char *path, void *watcherCtx){}
    zhandle_t *m_zh;
};

#endif
