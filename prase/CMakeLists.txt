cmake_minimum_required(VERSION 3.11.2)


project(prase)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
find_package(nlohmann_json 3.11.2 REQUIRED)

add_library(prase DeviceInfo.cpp UserInfo.cpp WgConfig.cpp)

target_link_libraries(prase PRIVATE nlohmann_json::nlohmann_json)