/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Master_H
#define Master_H

#include <thrift/TDispatchProcessor.h>
#include "master_types.h"



class MasterIf {
 public:
  virtual ~MasterIf() {}
  virtual void SubmitJob(std::string& _return, const JobInfo& job_info) = 0;
};

class MasterIfFactory {
 public:
  typedef MasterIf Handler;

  virtual ~MasterIfFactory() {}

  virtual MasterIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(MasterIf* /* handler */) = 0;
};

class MasterIfSingletonFactory : virtual public MasterIfFactory {
 public:
  MasterIfSingletonFactory(const boost::shared_ptr<MasterIf>& iface) : iface_(iface) {}
  virtual ~MasterIfSingletonFactory() {}

  virtual MasterIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(MasterIf* /* handler */) {}

 protected:
  boost::shared_ptr<MasterIf> iface_;
};

class MasterNull : virtual public MasterIf {
 public:
  virtual ~MasterNull() {}
  void SubmitJob(std::string& /* _return */, const JobInfo& /* job_info */) {
    return;
  }
};

typedef struct _Master_SubmitJob_args__isset {
  _Master_SubmitJob_args__isset() : job_info(false) {}
  bool job_info;
} _Master_SubmitJob_args__isset;

class Master_SubmitJob_args {
 public:

  Master_SubmitJob_args() {
  }

  virtual ~Master_SubmitJob_args() throw() {}

  JobInfo job_info;

  _Master_SubmitJob_args__isset __isset;

  void __set_job_info(const JobInfo& val) {
    job_info = val;
  }

  bool operator == (const Master_SubmitJob_args & rhs) const
  {
    if (!(job_info == rhs.job_info))
      return false;
    return true;
  }
  bool operator != (const Master_SubmitJob_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Master_SubmitJob_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Master_SubmitJob_pargs {
 public:


  virtual ~Master_SubmitJob_pargs() throw() {}

  const JobInfo* job_info;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Master_SubmitJob_result__isset {
  _Master_SubmitJob_result__isset() : success(false) {}
  bool success;
} _Master_SubmitJob_result__isset;

class Master_SubmitJob_result {
 public:

  Master_SubmitJob_result() : success() {
  }

  virtual ~Master_SubmitJob_result() throw() {}

  std::string success;

  _Master_SubmitJob_result__isset __isset;

  void __set_success(const std::string& val) {
    success = val;
  }

  bool operator == (const Master_SubmitJob_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const Master_SubmitJob_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Master_SubmitJob_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Master_SubmitJob_presult__isset {
  _Master_SubmitJob_presult__isset() : success(false) {}
  bool success;
} _Master_SubmitJob_presult__isset;

class Master_SubmitJob_presult {
 public:


  virtual ~Master_SubmitJob_presult() throw() {}

  std::string* success;

  _Master_SubmitJob_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class MasterClient : virtual public MasterIf {
 public:
  MasterClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  MasterClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void SubmitJob(std::string& _return, const JobInfo& job_info);
  void send_SubmitJob(const JobInfo& job_info);
  void recv_SubmitJob(std::string& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class MasterProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<MasterIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (MasterProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_SubmitJob(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  MasterProcessor(boost::shared_ptr<MasterIf> iface) :
    iface_(iface) {
    processMap_["SubmitJob"] = &MasterProcessor::process_SubmitJob;
  }

  virtual ~MasterProcessor() {}
};

class MasterProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  MasterProcessorFactory(const ::boost::shared_ptr< MasterIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< MasterIfFactory > handlerFactory_;
};

class MasterMultiface : virtual public MasterIf {
 public:
  MasterMultiface(std::vector<boost::shared_ptr<MasterIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~MasterMultiface() {}
 protected:
  std::vector<boost::shared_ptr<MasterIf> > ifaces_;
  MasterMultiface() {}
  void add(boost::shared_ptr<MasterIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void SubmitJob(std::string& _return, const JobInfo& job_info) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->SubmitJob(_return, job_info);
    }
    ifaces_[i]->SubmitJob(_return, job_info);
    return;
  }

};



#endif
