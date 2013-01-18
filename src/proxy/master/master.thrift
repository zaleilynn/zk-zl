struct VMInfo {
   1: string id,
   2: string type, 
   3: i32 vcpu, 
   4: i32 memory,
   5: string ip,
   6: string port,
   7: string os,
}

struct OSInfo {
   1: string os,
   2: i32 vcpu,
   3: i32 memory,
   4: i32 disk,
   5: string type,
}

struct AppInfo{
   1: string name,
   2: string source,
   3: string exe,
   4: string argument,
   5: string app_output,
   6: string job_output_dir,
   7: string destination,
   8: string run_type,
   9: i32 interval,
   10: string interval_exe,
   11: string interval_argument,
}

struct TaskInfo {
   1: string task_id,
   2: string job_id,
   3: string operate,
   4: AppInfo app_info,
   5: string worker_ip,
   6: VMInfo vm_info,
}

struct JobInfo {
   1: string operate,
   2: AppInfo app_info,
   3: OSInfo os_info,
   4: i32 instance,
}

service Master {
    string SubmitJob(1:JobInfo job_info)
}
