#include <fmt/core.h>
#include <fstream>
#include <filesystem>
#include "search.hpp"

std::vector<std::string> find_json_files(std::string dir, std::string keyword) {

    std::vector<std::string> files;
    std::ifstream fin;
    std::string filename;

    for (auto &p : std::filesystem::directory_iterator(dir)) {
        filename = p.path().filename().string();
        //printf(filename.data());

        if(filename.length() > 5 && filename.substr(filename.length() - 5) == ".json"){
            filename = filename.substr(0, filename.length() - 5);

            if (filename.find(keyword) != std::string::npos) {
                files.emplace_back( "   -> " + filename + show_package(p.path().string()));
            }
        }
    }

    return files;
}


std::vector<std::string> find_sub_dirs(std::string dir) {

    std::vector<std::string> dirs;
    std::ifstream fin;
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


std::vector<std::string> find_all_json_files(std::string dir, std::string keyword) {

    std::vector<std::string> files;
    std::vector<std::string> sub_dirs;
    std::vector<std::string> sub_dirss;
    std::vector<std::string> a;

    sub_dirs = find_sub_dirs(dir);

    for(auto &d : sub_dirs){
        a = find_sub_dirs(d);
        sub_dirss.insert(sub_dirss.end(), a.begin(), a.end());
    }

    for (auto &sub_dir : sub_dirss) {
        a = find_json_files(sub_dir, keyword);
        files.insert(files.end(), a.begin(), a.end());
    }

    return files;
}

bool search(std::string &keyword, std::vector<std::string> &result){
    std::vector<std::string> dirs = find_sub_dirs("..\\..\\..\\buckets");
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