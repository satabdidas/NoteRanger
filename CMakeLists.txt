cmake_minimum_required(VERSION 3.0)
project (NOTERANGER)

# Find Boost
find_package(Boost 1.61 REQUIRED regex filesystem system)

set(CMAKE_CXX_COMPILER /usr/local/bin/clang++-3.8)

add_definitions("-std=c++14")

# Include file path
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${Boost_INCLUDE_DIRS})

set(noteranger_srcs ${PROJECT_SOURCE_DIR}/src/Parser.cpp
                    ${PROJECT_SOURCE_DIR}/src/TermDB.cpp
                    ${PROJECT_SOURCE_DIR}/src/DocumentDB.cpp)

add_executable(noteranger ${PROJECT_SOURCE_DIR}/src/Main.cpp ${noteranger_srcs})

target_link_libraries(noteranger ${Boost_LIBRARIES})
