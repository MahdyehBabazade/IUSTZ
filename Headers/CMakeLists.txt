cmake_minimum_required(VERSION 3.26)
project(Headers)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Headers
        .idea/.gitignore
        .idea/Headers.iml
        .idea/modules.xml
        .idea/vcs.xml
        items.h)
