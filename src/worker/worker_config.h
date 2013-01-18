#ifndef ZLYNN_SRC_WORKER_WORKER_CONFIG_H_
#define ZLYNN_SRC_WORKER_WORKER_CONFIG_H_

#include <map>
#include "common/singleton.h"

using std::map;

class WorkerConfig {
public:
   bool Init(const string& conf_file); 
   string Get(const string& name);
private:
   map<string, string> m_attr_map;
};

typedef Singleton<WorkerConfig> WorkerConfigI;

#endif
