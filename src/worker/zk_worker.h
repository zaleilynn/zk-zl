#ifndef ZLYNN_SRC_WORKER_ZK_WORKER_H_
#define ZLYNN_SRC_WORKER_ZK_WORKER_H_

#include "common/singleton.h"
#include "common/zk.h"

using std::string;

class ZKWorker : public ZK {
public:
    bool Init();
}; 

typedef Singleton<ZKWorker> ZKWorkerI;

#endif 
