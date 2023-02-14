add_rules("mode.debug", "mode.release")
add_requires("fmt", "nlohmann_json")
if is_mode("debug") then
    add_defines("DEBUG")
end

target("sf")
    set_kind("binary")
    add_files("src/*.cpp")
    set_languages("cxx20")
    set_optimize("fastest")
    add_packages("fmt", "nlohmann_json")