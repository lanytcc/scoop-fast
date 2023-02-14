#include <fmt/core.h>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include "search.hpp"

std::string lower(std::string a){
    std::string res = a;
    for(auto &i:res){
        if(i >= 'A' && i <= 'Z'){
            i = 'a' + i - 'A';
        }
    }
    return res;
}

std::vector<std::string> find_json_files(std::string dir, std::string keyword) {

    std::vector<std::string> files;
    std::string filename;

    for (auto &p : std::filesystem::directory_iterator(dir)) {
        filename = p.path().filename().string();
        //printf(filename.data());

        if(filename.length() > 5 && filename.substr(filename.length() - 5) == ".json"){
            filename = filename.substr(0, filename.length() - 5);

            if (lower(filename).find(lower(keyword)) != std::string::npos) {
                files.emplace_back( "   -> " + filename + show_package(p.path()));
            }
        }
    }

    return files;
}


std::vector<std::string> find_sub_dirs(std::string dir) {

    std::vector<std::string> dirs;
    std::string filename;

    for (auto &p : std::filesystem::directory_iterator(dir)) {
        filename = p.path().string();
        //printf(filename.data());
        if (std::filesystem::is_directory(filename)) {
            dirs.emplace_back(filename);
        }
    }

    return dirs;
}

bool search(std::string &keyword, std::vector<std::string> &result){
    char buffer[MAX_PATH];
    ExpandEnvironmentStrings("%USERPROFILE%", buffer, MAX_PATH);

    std::vector<std::string> dirs = find_sub_dirs(buffer + std::string("\\scoop\\buckets"));
    std::vector<std::string> a;
    
    for(auto &p : dirs){
#ifdef DEBUG
        printf(p.data());
#endif
        a = find_json_files(p + "\\bucket", keyword);
        result.insert(result.end(), a.begin(), a.end());
    }
    return true;
}