#include <stdio.h>
#include <zookeeper/zookeeper.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "proxy/master/gen-cpp/Master.h"
#include "common/rpc.h"

//string master_endpoint = "10.128.252.128:9999";
string master_endpoint = "172.16.19.212:9999";

using namespace std;

int32_t main(int argc, char* argv[]){
    JobInfo job_info;
    job_info.operate = "auto";
    job_info.instance = 2;

    job_info.os_info.vcpu = 1;
    job_info.os_info.memory = 1024;
    job_info.os_info.disk = 10;
    job_info.os_info.type = "kvm";
    job_info.os_info.os = "winxp";

    job_info.app_info.name = "test";
    job_info.app_info.source = "/home/zaleilynn/ftp/test.zip";
    job_info.app_info.exe = "run.bat";
    job_info.app_info.run_type = "normal";

    Proxy<MasterClient> proxy =  Rpc<MasterClient, MasterClient>::GetProxy(master_endpoint);
    int64_t rtn = proxy().SubmitJob(job_info);
    
    if(rtn == -1){
        printf("error\n");
        return -1;
    }
    printf("submit success, job id:%ld\n" ,rtn);
    return 0;
}

