#ifndef ZLYNN_SRC_MASTER_JOB_H_
#define ZLYNN_SRC_MASTER_JOB_H_

#include <stdint.h>
#include <boost/shared_ptr.hpp>
#include "master/master_service.h"
#include "common/block_queue.h"
#include "common/singleton.h"

using zlynn::BlockQueue;
using boost::shared_ptr;

class Job {
public:
    Job(const JobInfo& job_info);
    bool Init();
    void Do();
    bool SetJobStatus(const string &status);
    string GetJobStatus();
    string GetJobId(){
        return m_id;
    }
private:
    //以下两个东西是一样的,为了方便保存两个格式的id
    string m_id;
    JobInfo m_info;
};

typedef shared_ptr<Job> JobPtr;

typedef Singleton<BlockQueue<JobPtr> > JobBufferI;
#endif
