#ifndef ZLYNN_SRC_WORKER_RESOURCE_MANAGER_H_
#define ZLYNN_SRC_WORKER_RESOURCE_MANAGER_H_

#include <string>
#include "common/singleton.h"

using std::string;

class ResourceManager {
public:
   bool Init();
   ~ResourceManager();
   string GetCommunicationIp(); 
private:
   string m_communication_ip;
   string m_bridge_ip;
   string m_rpc_port;
   int32_t m_total_vcpu;
   int32_t m_total_memory;
};

typedef Singleton<ResourceManager> ResourceManagerI;
#endif
