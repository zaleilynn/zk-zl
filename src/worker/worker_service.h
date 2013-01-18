#ifndef ZLYNN_SRC_WORKER_WORKER_SERVICE_H_
#define ZLYNN_SRC_WORKER_WORKER_SERVICE_H_

#include <stdint.h>
#include "proxy/worker/gen-cpp/Worker.h"

#include <string>

using std::string;

class WorkerService : public WorkerIf {
public:
    bool StartTask(const TaskInfo& task_info);
};

#endif
