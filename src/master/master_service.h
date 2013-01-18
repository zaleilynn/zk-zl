#ifndef ZLYNN_SRC_MASTER_MASTER_SERVICE_H_
#define ZLYNN_SRC_MASTER_MASTER_SERVICE_H_

#include <stdint.h>
#include "proxy/master/gen-cpp/Master.h"

#include <string>

using std::string;

class MasterService : public MasterIf {
public:
    void SubmitJob(string& job_id, const JobInfo& job_info);
};

#endif
