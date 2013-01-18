#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include "common/rapidxml.hpp"
#include "common/rapidxml_utils.hpp"
#include "master/master_config.h"

using log4cplus::Logger;
using rapidxml::file;
using rapidxml::xml_document;
using rapidxml::xml_node;
using rapidxml::xml_attribute;

Logger logger = Logger::getInstance("master");

bool MasterConfig::Init(const string& conf_file){
    xml_document<> doc;
    try {
        file<> fdoc(conf_file.c_str());
        doc.parse<0>(fdoc.data());
    } catch (rapidxml::parse_error& ex) {
        LOG4CPLUS_ERROR(logger, "synex error in " << ex.what());
        return false;
    } catch (std::runtime_error& ex) {
        LOG4CPLUS_ERROR(logger, "error in reading master config " << ex.what());
        return false;
    } 
    xml_node<> *root = doc.first_node("master");
    
    if(!root) {
        LOG4CPLUS_ERROR(logger, "no master specified");
        return false;
    }
    xml_node<> *node1;

    node1 = root->first_node("zk_endpoint");
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
    return true;
}

string MasterConfig::Get(const string& name) {
    map<string, string>::iterator it = m_attr_map.find(name);
    if (it != m_attr_map.end())
        return it->second;
    else
        return string();
}
