#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include "json.hpp"
using json = nlohmann::json;


json open(const std::filesystem::path &file){
    std::ifstream f(file);
    return json::parse(f);
}

std::string show_package(const std::filesystem::path &dir){
    std::ostringstream usage;
    json file;
    file = open(dir);
    usage << " - " << file["version"] << ": " << file["description"];
    return usage.str();
}