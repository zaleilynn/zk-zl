#include <boost/thread.hpp>
#include "master/job.h"

using boost::thread;

void* JobWorker(JobPtr job){ 
    job->Do();
    return NULL;
}

void* JobProcessor(){
    while(true) {
        JobPtr job;
        JobBufferI::Instance()->PopFront(&job);
        thread job_worker_t(JobWorker, job);
    }
    return NULL;
}
