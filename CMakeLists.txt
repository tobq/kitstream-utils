cmake_minimum_required(VERSION 3.19)
project(utils)
include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

# fetch xxhash
FetchContent_Declare(xxhash
        GIT_REPOSITORY https://github.com/Cyan4973/xxHash
        GIT_TAG release)
FetchContent_GetProperties(xxhash)
if (NOT xxhash_POPULATED)
    FetchContent_Populate(xxhash)
    add_subdirectory(${xxhash_SOURCE_DIR}/cmake_unofficial ${xxhash_BINARY_DIR})
endif ()
# add fetched libs to this project
FetchContent_MakeAvailable(xxhash)

########## fetch fmt
FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG master)
FetchContent_MakeAvailable(fmt)


add_library(utils src/main.cpp)

target_include_directories(utils PUBLIC src)
target_link_libraries(utils
        fmt::fmt
        xxhash
        )