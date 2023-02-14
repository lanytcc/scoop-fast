#include <fstream>
#include <nlohmann/json.hpp>
#include <stdio.h>
#include "json.hpp"
using json = nlohmann::json;


json open(std::string &file){
    std::ifstream f(file);
    return json::parse(f);
}

std::string show_package(std::string dir){
    std::string usage;
    json file;
    file = open(dir);
    usage += " - ";
    usage += file["version"];
    usage += ": ";
    usage += file["description"];
    return usage;
}