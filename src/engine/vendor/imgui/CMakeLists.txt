add_library(imgui STATIC
    imgui_impl_opengl3.cpp
    imgui_impl_opengl3.h
    imgui_impl_sdl.cpp
    imgui_impl_sdl.h)

target_include_directories(imgui PUBLIC ".")

target_link_libraries(imgui CONAN_PKG::imgui CONAN_PKG::glew CONAN_PKG::sdl2)