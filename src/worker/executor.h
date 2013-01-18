#ifndef ZLYNN_SRC_WORKER_EXECUTOR_H_
#define ZLYNN_SRC_WORKER_EXECUTOR_H_

#include <string>
#include <boost/shared_ptr.hpp>
#include "common/block_queue.h"
#include "common/singleton.h"
#include "proxy/master/gen-cpp/Master.h"


using std::string;
using boost::shared_ptr;
using zlynn::BlockQueue;

class Executor {
public:
    Executor(const TaskInfo& info);
    bool Init();
    void Do();
    bool SetExecutorStatus(const string &status);
    string GetExecutorStatus();
private:
    TaskInfo m_info;
};

typedef shared_ptr<Executor> ExecutorPtr;

typedef Singleton<BlockQueue<ExecutorPtr> > ExecutorBufferI;
#endif
