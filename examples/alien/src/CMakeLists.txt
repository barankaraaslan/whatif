include(maven.cmake)

cmake_minimum_required(VERSION 3.14) # install(TARGETS) which installs files to correct destinations by default requires 3.14
project(alien VERSION 0.1.1 DESCRIPTION "A software just appeared on a disk" LANGUAGES CXX)

find_package(log4cpp ${log4cpp_VERSION} REQUIRED)

# Collect all cpp source files
file(GLOB_RECURSE Sources LIST_DIRECTORIES FALSE CONFIGURE_DEPENDS *.cpp)

add_executable(alien ${Sources})

target_link_libraries(alien PRIVATE log4cpp::log4cpp)

install(TARGETS alien)
include(CPack)
