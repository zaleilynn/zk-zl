#include <boost/thread.hpp>
#include "worker/executor.h"

using boost::thread;

void* ExecutorWorker(ExecutorPtr executor){
    executor->Do();
    return NULL;
}

void* ExecutorProcessor(){
    while(true) { 
        ExecutorPtr executor;
        ExecutorBufferI::Instance()->PopFront(&executor);
        thread executor_worker_t(ExecutorWorker, executor);
    }
    return NULL;
}
