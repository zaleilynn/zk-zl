#include <stdio.h>
#include <zookeeper/zookeeper.h>
#include <errno.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <classad/classad.h>
#include <classad/classad_distribution.h>

using std::string;

int32_t main(int argc, char* argv[]){
    ClassAd        classad;
    ClassAdParser  parser;

    classad.InsertAttr("memory", 5000);
    classad.InsertAttr("vcpu", 12);
   
    string printed_classad;
    ClassAdUnParser unparser;
    unparser.Unparse(printed_classad, &classad);
    printf("%s\n", printed_classad.c_str());
 
    return 0;
}

