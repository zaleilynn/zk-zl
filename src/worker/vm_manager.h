#ifndef ZLYNN_SRC_WORKER_VM_MANAGER_H_
#define ZLYNN_SRC_WORKER_VM_MANAGER_H_

#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>

#include "common/singleton.h"

class VMManager {
public:
    VMManager();
    ~VMManager();
    bool Init(const string& vm_template);
    bool CreateVM(const string& xml_desc);
private:
    virConnectPtr m_qemu_conn;
    string m_vm_template;
};

typedef Singleton<VMManager> VMManagerI;
#endif

