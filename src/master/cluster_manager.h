#ifndef ZLYNN_SRC_MASTER_CLUSTER_MANAGER_H_
#define ZLYNN_SRC_MASTER_CLUSTER_MANAGER_H_

#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include "common/singleton.h"

class ClusterManager {
public:
    bool ReleaseResourceOnMachine(const string& machine, const ClassAd& res);
    string AllocateResource(const ClassAd& resource);
    bool AllocateResourceOnMachine(const string& machine, const ClassAd& res);
    string GetMachineRPCEndpoint(const string& machine);
};

typedef Singleton<ClusterManager> ClusterManagerI;
#endif


