#include <stdio.h>
#include <zookeeper/zookeeper.h>
#include <errno.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

int32_t main(int argc, char* argv[]){
    std::vector<std::string> strs;
    boost::split(strs, "string:to:split", boost::is_any_of(":"));
    for(unsigned i = 0; i < strs.size(); i++) {
        printf("%s\n", strs[i].c_str());
    }
    return 0;
}

