#include <fmt/core.h>
#include <string>
#include <vector>
#include <cstdlib>
#include "search.hpp"
using std::string;
using std::vector;

string order(int argc, char** argv){
    string o;
    for(int i = 1; i < argc; ++i){
        o += " " + string(argv[i]);
    }
    return "scoop " + o;
}

int main(int argc, char** argv){
    if(argc <= 1)return 0;

#ifdef DEBUG
    fmt::print(" {0} argc\n", argc);
#endif

    bool _search = false;
    int cnt = 0;
    for(int i = 0; i < argc; ++i){
        if(string(argv[1]) == "search"){
            _search = true;
        }
        else {
            system(order(argc, argv).data());
        }
    }

    vector<string> res;
    string keyword = string(argv[2]);

#ifdef DEBUG
    //fmt::print(" {0} key\n", keyword);
#endif
    
    fmt::print("Searching...\n\n");
    if(_search){
        search(keyword, res);
        for(auto &i : res){
            fmt::print("{0}\n", i);
        }
        if(res.size() == 0){
            fmt::print("Nothing!\n");
        }
    }

    return 0;
}