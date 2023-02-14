add_rules("mode.debug", "mode.release")
add_requires("fmt", "nlohmann_json")

target("scoop-fast")
    set_kind("binary")
    add_files("src/*.cpp")
    set_languages("cxx20")
    set_optimize("fastest")
    mode("debug")
        add_defines("DEBUG")
    add_packages("fmt", "nlohmann_json")