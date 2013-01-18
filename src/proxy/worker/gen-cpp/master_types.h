/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef master_TYPES_H
#define master_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>





typedef struct _VMInfo__isset {
  _VMInfo__isset() : id(false), type(false), vcpu(false), memory(false), ip(false), port(false), os(false) {}
  bool id;
  bool type;
  bool vcpu;
  bool memory;
  bool ip;
  bool port;
  bool os;
} _VMInfo__isset;

class VMInfo {
 public:

  static const char* ascii_fingerprint; // = "6F4A3F3C9334B20E5D200C57F5FDFA70";
  static const uint8_t binary_fingerprint[16]; // = {0x6F,0x4A,0x3F,0x3C,0x93,0x34,0xB2,0x0E,0x5D,0x20,0x0C,0x57,0xF5,0xFD,0xFA,0x70};

  VMInfo() : id(), type(), vcpu(0), memory(0), ip(), port(), os() {
  }

  virtual ~VMInfo() throw() {}

  std::string id;
  std::string type;
  int32_t vcpu;
  int32_t memory;
  std::string ip;
  std::string port;
  std::string os;

  _VMInfo__isset __isset;

  void __set_id(const std::string& val) {
    id = val;
  }

  void __set_type(const std::string& val) {
    type = val;
  }

  void __set_vcpu(const int32_t val) {
    vcpu = val;
  }

  void __set_memory(const int32_t val) {
    memory = val;
  }

  void __set_ip(const std::string& val) {
    ip = val;
  }

  void __set_port(const std::string& val) {
    port = val;
  }

  void __set_os(const std::string& val) {
    os = val;
  }

  bool operator == (const VMInfo & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(type == rhs.type))
      return false;
    if (!(vcpu == rhs.vcpu))
      return false;
    if (!(memory == rhs.memory))
      return false;
    if (!(ip == rhs.ip))
      return false;
    if (!(port == rhs.port))
      return false;
    if (!(os == rhs.os))
      return false;
    return true;
  }
  bool operator != (const VMInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const VMInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(VMInfo &a, VMInfo &b);

typedef struct _OSInfo__isset {
  _OSInfo__isset() : os(false), vcpu(false), memory(false), disk(false), type(false) {}
  bool os;
  bool vcpu;
  bool memory;
  bool disk;
  bool type;
} _OSInfo__isset;

class OSInfo {
 public:

  static const char* ascii_fingerprint; // = "DCC01FA63FCBA4D0569C45486D898970";
  static const uint8_t binary_fingerprint[16]; // = {0xDC,0xC0,0x1F,0xA6,0x3F,0xCB,0xA4,0xD0,0x56,0x9C,0x45,0x48,0x6D,0x89,0x89,0x70};

  OSInfo() : os(), vcpu(0), memory(0), disk(0), type() {
  }

  virtual ~OSInfo() throw() {}

  std::string os;
  int32_t vcpu;
  int32_t memory;
  int32_t disk;
  std::string type;

  _OSInfo__isset __isset;

  void __set_os(const std::string& val) {
    os = val;
  }

  void __set_vcpu(const int32_t val) {
    vcpu = val;
  }

  void __set_memory(const int32_t val) {
    memory = val;
  }

  void __set_disk(const int32_t val) {
    disk = val;
  }

  void __set_type(const std::string& val) {
    type = val;
  }

  bool operator == (const OSInfo & rhs) const
  {
    if (!(os == rhs.os))
      return false;
    if (!(vcpu == rhs.vcpu))
      return false;
    if (!(memory == rhs.memory))
      return false;
    if (!(disk == rhs.disk))
      return false;
    if (!(type == rhs.type))
      return false;
    return true;
  }
  bool operator != (const OSInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const OSInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(OSInfo &a, OSInfo &b);

typedef struct _AppInfo__isset {
  _AppInfo__isset() : name(false), source(false), exe(false), argument(false), app_output(false), job_output_dir(false), destination(false), run_type(false), interval(false), interval_exe(false), interval_argument(false) {}
  bool name;
  bool source;
  bool exe;
  bool argument;
  bool app_output;
  bool job_output_dir;
  bool destination;
  bool run_type;
  bool interval;
  bool interval_exe;
  bool interval_argument;
} _AppInfo__isset;

class AppInfo {
 public:

  static const char* ascii_fingerprint; // = "8712088E233655800317F6EEBDC80D2E";
  static const uint8_t binary_fingerprint[16]; // = {0x87,0x12,0x08,0x8E,0x23,0x36,0x55,0x80,0x03,0x17,0xF6,0xEE,0xBD,0xC8,0x0D,0x2E};

  AppInfo() : name(), source(), exe(), argument(), app_output(), job_output_dir(), destination(), run_type(), interval(0), interval_exe(), interval_argument() {
  }

  virtual ~AppInfo() throw() {}

  std::string name;
  std::string source;
  std::string exe;
  std::string argument;
  std::string app_output;
  std::string job_output_dir;
  std::string destination;
  std::string run_type;
  int32_t interval;
  std::string interval_exe;
  std::string interval_argument;

  _AppInfo__isset __isset;

  void __set_name(const std::string& val) {
    name = val;
  }

  void __set_source(const std::string& val) {
    source = val;
  }

  void __set_exe(const std::string& val) {
    exe = val;
  }

  void __set_argument(const std::string& val) {
    argument = val;
  }

  void __set_app_output(const std::string& val) {
    app_output = val;
  }

  void __set_job_output_dir(const std::string& val) {
    job_output_dir = val;
  }

  void __set_destination(const std::string& val) {
    destination = val;
  }

  void __set_run_type(const std::string& val) {
    run_type = val;
  }

  void __set_interval(const int32_t val) {
    interval = val;
  }

  void __set_interval_exe(const std::string& val) {
    interval_exe = val;
  }

  void __set_interval_argument(const std::string& val) {
    interval_argument = val;
  }

  bool operator == (const AppInfo & rhs) const
  {
    if (!(name == rhs.name))
      return false;
    if (!(source == rhs.source))
      return false;
    if (!(exe == rhs.exe))
      return false;
    if (!(argument == rhs.argument))
      return false;
    if (!(app_output == rhs.app_output))
      return false;
    if (!(job_output_dir == rhs.job_output_dir))
      return false;
    if (!(destination == rhs.destination))
      return false;
    if (!(run_type == rhs.run_type))
      return false;
    if (!(interval == rhs.interval))
      return false;
    if (!(interval_exe == rhs.interval_exe))
      return false;
    if (!(interval_argument == rhs.interval_argument))
      return false;
    return true;
  }
  bool operator != (const AppInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const AppInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(AppInfo &a, AppInfo &b);

typedef struct _TaskInfo__isset {
  _TaskInfo__isset() : task_id(false), job_id(false), operate(false), app_info(false), worker_ip(false), vm_info(false) {}
  bool task_id;
  bool job_id;
  bool operate;
  bool app_info;
  bool worker_ip;
  bool vm_info;
} _TaskInfo__isset;

class TaskInfo {
 public:

  static const char* ascii_fingerprint; // = "2BB50CE26058BE8A612CC6A44252F0BF";
  static const uint8_t binary_fingerprint[16]; // = {0x2B,0xB5,0x0C,0xE2,0x60,0x58,0xBE,0x8A,0x61,0x2C,0xC6,0xA4,0x42,0x52,0xF0,0xBF};

  TaskInfo() : task_id(), job_id(), operate(), worker_ip() {
  }

  virtual ~TaskInfo() throw() {}

  std::string task_id;
  std::string job_id;
  std::string operate;
  AppInfo app_info;
  std::string worker_ip;
  VMInfo vm_info;

  _TaskInfo__isset __isset;

  void __set_task_id(const std::string& val) {
    task_id = val;
  }

  void __set_job_id(const std::string& val) {
    job_id = val;
  }

  void __set_operate(const std::string& val) {
    operate = val;
  }

  void __set_app_info(const AppInfo& val) {
    app_info = val;
  }

  void __set_worker_ip(const std::string& val) {
    worker_ip = val;
  }

  void __set_vm_info(const VMInfo& val) {
    vm_info = val;
  }

  bool operator == (const TaskInfo & rhs) const
  {
    if (!(task_id == rhs.task_id))
      return false;
    if (!(job_id == rhs.job_id))
      return false;
    if (!(operate == rhs.operate))
      return false;
    if (!(app_info == rhs.app_info))
      return false;
    if (!(worker_ip == rhs.worker_ip))
      return false;
    if (!(vm_info == rhs.vm_info))
      return false;
    return true;
  }
  bool operator != (const TaskInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TaskInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(TaskInfo &a, TaskInfo &b);

typedef struct _JobInfo__isset {
  _JobInfo__isset() : operate(false), app_info(false), os_info(false), instance(false) {}
  bool operate;
  bool app_info;
  bool os_info;
  bool instance;
} _JobInfo__isset;

class JobInfo {
 public:

  static const char* ascii_fingerprint; // = "C281E19CB6D2888CCE5071A00FC3E879";
  static const uint8_t binary_fingerprint[16]; // = {0xC2,0x81,0xE1,0x9C,0xB6,0xD2,0x88,0x8C,0xCE,0x50,0x71,0xA0,0x0F,0xC3,0xE8,0x79};

  JobInfo() : operate(), instance(0) {
  }

  virtual ~JobInfo() throw() {}

  std::string operate;
  AppInfo app_info;
  OSInfo os_info;
  int32_t instance;

  _JobInfo__isset __isset;

  void __set_operate(const std::string& val) {
    operate = val;
  }

  void __set_app_info(const AppInfo& val) {
    app_info = val;
  }

  void __set_os_info(const OSInfo& val) {
    os_info = val;
  }

  void __set_instance(const int32_t val) {
    instance = val;
  }

  bool operator == (const JobInfo & rhs) const
  {
    if (!(operate == rhs.operate))
      return false;
    if (!(app_info == rhs.app_info))
      return false;
    if (!(os_info == rhs.os_info))
      return false;
    if (!(instance == rhs.instance))
      return false;
    return true;
  }
  bool operator != (const JobInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const JobInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(JobInfo &a, JobInfo &b);



#endif