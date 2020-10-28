add_library(lake-engine STATIC
        "Game.cpp" "Game.hpp"
        "GameController.cpp" "GameController.hpp"
        "ImGuiHelper.hpp")

add_subdirectory(vendor/imgui)

target_include_directories(lake-engine PUBLIC ".")

target_link_libraries(lake-engine PUBLIC
        project_options
        project_warnings
        imgui
        CONAN_PKG::sdl2
        CONAN_PKG::fmt
        CONAN_PKG::glew
        CONAN_PKG::spdlog)