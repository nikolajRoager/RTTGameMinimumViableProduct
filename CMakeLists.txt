cmake_minimum_required(VERSION 4.0)
project(PreMVPMapGame)

set(CMAKE_CXX_STANDARD 20)


include_directories("include")

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 sdl2)
pkg_check_modules(SDL2_image SDL2_image)
pkg_check_modules(SDL2_ttf SDL2_ttf)
pkg_check_modules(SDL2_mixer SDL2_mixer)
link_libraries(${SDL2_LIBRARIES})
link_libraries(${SDL2_image_LIBRARIES})
link_libraries(${SDL2_mixer_LIBRARIES})
link_libraries(${SDL2_ttf_LIBRARIES})


add_executable(PreMVPMapGame main.cpp
        src/engine.cpp
        src/scenarios.cpp
)
