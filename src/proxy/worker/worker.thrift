include "../master/master.thrift"

service Worker {
    bool StartTask(1: master.TaskInfo task_info)
}
