#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include "worker/vm_manager.h"
#include <fstream>
#include <sstream>

using std::ifstream;
using std::stringstream;

using log4cplus::Logger;

static Logger logger = Logger::getInstance("worker");

VMManager::VMManager(){
    m_vm_template = "";
}

VMManager::~VMManager(){
    virConnectClose(m_qemu_conn);
}

bool VMManager::Init(const string& vm_template){
    m_qemu_conn = virConnectOpen("qemu:///system");
    if(m_qemu_conn == NULL) {
        LOG4CPLUS_ERROR(logger, "cannot open connection to qemu:///system"); 
        return false;
    }

    ifstream file(vm_template.c_str());
    if(!file) {
        LOG4CPLUS_ERROR(logger, "cannot open open file" + vm_template); 
        return false;
    }

    //先把XML模板给读出来
    stringstream buffer;
    buffer << file.rdbuf();
    m_vm_template = buffer.str();
    file.close();

    return true;
}

bool VMManager::CreateVM(const string& xml_desc){
    virDomainPtr vm_ptr = virDomainCreateXML(m_qemu_conn, xml_desc.c_str(), 0);
    if(!vm_ptr) {
        virErrorPtr error = virGetLastError();
        LOG4CPLUS_ERROR(logger, error->message);  
        return false;
    }
    return true;
}
