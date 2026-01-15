cmake_minimum_required(VERSION 3.10)
project(Simplebrowse C)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
find_package(CURL REQUIRED)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_executable(simplebrowse src/main.c)

target_link_libraries(simplebrowse PRIVATE ${GTK3_LIBRARIES} CURL::libcurl)

install(TARGETS simplebrowse DESTINATION bin)
