cmake_minimum_required(VERSION 3.11.2)

project(cliApi)

include_directories(
    prase
    protos
    ${_PROTOBUF_INCLUDE_DIR}
)

add_subdirectory(protos)
add_subdirectory(prase)


# CXX standard
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")



#set protobuf
set(protobuf_MODULE_COMPATIBLE True)
find_package(Protobuf REQUIRED)
set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)

# set grpc
find_package(gRPC REQUIRED)
set(_GRPC_GRPCPP_UNSECURE gRPC::grpc++_unsecure)

# set  json
find_package(nlohmann_json 3.11.2 REQUIRED)

set(SOURCES
    ser.cpp
)

add_executable(ser ${SOURCES})

target_link_libraries(ser
    PUBLIC prase
    PUBLIC protos
    PRIVATE nlohmann_json::nlohmann_json
    ${_GRPC_GRPCPP_UNSECURE}
    ${_PROTOBUF_LIBPROTOBUF}
)

add_executable(cli cli.cpp)

target_link_libraries(cli
    PUBLIC prase
    PUBLIC protos
    PRIVATE nlohmann_json::nlohmann_json
    ${_GRPC_GRPCPP_UNSECURE}
    ${_PROTOBUF_LIBPROTOBUF}
)
