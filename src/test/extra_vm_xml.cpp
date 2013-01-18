#include "common/rapidxml.hpp"
#include "common/rapidxml_utils.hpp"
#include <string>
#include <fstream>
#include <sstream>

using rapidxml::file;
using rapidxml::xml_document;
using rapidxml::xml_node;
using rapidxml::xml_attribute;

using std::ifstream;
using std::stringstream;
using std::string;

int main(int argc, char* argv[]){
    string conf_file = "vm.xml";
    xml_document<> doc;
    try {
        file<> fdoc(conf_file.c_str());
        doc.parse<0>(fdoc.data());
    } catch (rapidxml::parse_error& ex) {
        return -1;
    } catch (std::runtime_error& ex) {
        return -1;
    }
    xml_node<> *root = doc.first_node("extra");

    if(!root) {
        return -1;
    }

    xml_node<> *node1;
 
    node1 = root->first_node("test1");
    if(!node1) {
        return -1;
    }
    printf("%s\n", node1->value());

    node1 = root->first_node("test2");
    if(!node1) {
        return -1;
    }

    printf("%s\n", node1->value());
    
    ifstream config_file(conf_file.c_str());   
    if(!config_file) {
        return -1;
    } 
    stringstream buffer;
    buffer << config_file.rdbuf();
    string content = buffer.str(); 
    printf("%s\n", content.c_str());
    config_file.close();
    return 0;
}

