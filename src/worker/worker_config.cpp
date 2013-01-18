#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include "common/rapidxml.hpp"
#include "common/rapidxml_utils.hpp"
#include "worker/worker_config.h"

using log4cplus::Logger;
using rapidxml::file;
using rapidxml::xml_document;
using rapidxml::xml_node;
using rapidxml::xml_attribute;

static Logger logger = Logger::getInstance("master");

bool WorkerConfig::Init(const string& conf_file){
    xml_document<> doc;
    try {
        file<> fdoc(conf_file.c_str());
        doc.parse<0>(fdoc.data());
    } catch (rapidxml::parse_error& ex) {
        LOG4CPLUS_ERROR(logger, "synex error in " << ex.what());
        return false;
    } catch (std::runtime_error& ex) {
        LOG4CPLUS_ERROR(logger, "task xml error: " << ex.what());
        return false;
    } 
    xml_node<> *root = doc.first_node("worker");
    
    if(!root) {
        LOG4CPLUS_ERROR(logger, "no worker specified");
        return false;
    }
    xml_node<> *node1;
    
    node1 = root->first_node("master_endpoint");
    if(!node1) { 
        LOG4CPLUS_ERROR(logger, "no master endpoint specified");
        return false;
    }

    m_attr_map["master_endpoint"] = node1->value();
 
    node1 = node1->next_sibling("zk_endpoint");
    if(!node1) {
        LOG4CPLUS_ERROR(logger, "no zk_endpoint specified");
        return false;
    }
    m_attr_map["zk_endpoint"] = node1->value(); 
   
    node1 = node1->next_sibling("rpc_port");
    if(!node1) { 
        LOG4CPLUS_ERROR(logger, "no rpc port specified");
        return false;
    }
    m_attr_map["rpc_port"] = node1->value();
 
    node1 = node1->next_sibling("bridge_interface");
    if(!node1) {
        LOG4CPLUS_ERROR(logger, "no bridge interface specified");
        return false;
    }
    m_attr_map["bridge_interface"] = node1->value();

    node1 = node1->next_sibling("communication_interface");
    if(!node1) {
        LOG4CPLUS_ERROR(logger, "no communication interface specified");
        return false;
    }
    m_attr_map["communication_interface"] = node1->value();


    node1 = node1->next_sibling("inner_interface");
    if(!node1) {
        LOG4CPLUS_ERROR(logger, "no inner interface specified");
        return false;
    }
    m_attr_map["inner_interface"] = node1->value();
    
    node1 = node1->next_sibling("outter_interface");
    if(!node1) {
        LOG4CPLUS_ERROR(logger, "no outter interface specified");
        return false;
    }
    m_attr_map["outter_interface"] = node1->value();
    return true;
}

string WorkerConfig::Get(const string& name) {
    map<string, string>::iterator it = m_attr_map.find(name);
    if (it != m_attr_map.end())
        return it->second;
    else
        return string();
}
