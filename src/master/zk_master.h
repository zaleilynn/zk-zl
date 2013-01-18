#ifndef ZLYNN_SRC_MASTER_ZK_MASTER_H_
#define ZLYNN_SRC_MASTER_ZK_MASTER_H_

#include "common/singleton.h"
#include "common/zk.h"

using std::string;

class ZKMaster : public ZK {
public:
    bool Init();
}; 

typedef Singleton<ZKMaster> ZKMasterI;

#endif 
