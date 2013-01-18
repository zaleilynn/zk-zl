#ifndef ZLYNN_SRC_MASTER_MASTER_CONFIG_H_
#define ZLYNN_SRC_MASTER_MASTER_CONFIG_H_ 

#include <map>
#include "common/singleton.h"

using std::map;

class MasterConfig {
public:
   bool Init(const string& conf_file); 
   string Get(const string& name);
private:
   map<string, string> m_attr_map;
};

typedef Singleton<MasterConfig> MasterConfigI;

#endif
