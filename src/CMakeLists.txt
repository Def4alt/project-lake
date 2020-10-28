add_subdirectory("engine")

add_executable(project-lake main.cpp)

target_link_libraries(project-lake PRIVATE
        project_options
        project_warnings
        lake-engine
        CONAN_PKG::docopt.cpp)
