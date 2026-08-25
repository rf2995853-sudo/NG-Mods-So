cmake_minimum_required(VERSION 3.22.1)
project("ngmods")

add_library(
    ngmods
    SHARED
    main.cpp
)

find_library(log-lib log)

target_link_libraries(
    ngmods
    ${log-lib}
)
