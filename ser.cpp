
#include <iostream>
#include <algorithm>
#include <cstring>
#include <memory>
#include <fstream>
#include <nlohmann/json.hpp>
#include <grpcpp/grpcpp.h>
#include <grpcpp/channel.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/security/credentials.h>

#include "./prase/DeviceInfo.h"
#include "./prase/UserInfo.h"
#include "./prase/WgConfig.h"
#include "./protos/hybrid_scope.grpc.pb.h"
#include "./protos/hybrid_scope.pb.h"

using namespace grpc;

class wgserver final: public hybrid_scope::Wg::Service {
    Status sync_config(ServerContext* context,
                const hybrid_scope::WgConfigRequest& wg_config,
                hybrid_scope::RpcResult* rpc_config)  
    {
        std::cout << wg_config.box_id() << std::endl;
        return Status::OK;
    }
    Status startup(ServerContext* context,
                const hybrid_scope::WgStartupRequest& wg_start_up,
                hybrid_scope::RpcResult* rpc_config)  
    {
        std::cout << wg_start_up.id() << std::endl;
        return Status::OK;
    }
    Status shutdown(ServerContext* context,
                const hybrid_scope::WgShutdownRequest& wg_shut_down,
                hybrid_scope::RpcResult* rpc_config) 
    {
        std::cout << wg_shut_down.id() << std::endl;
        return Status::OK;
    }
    Status exec(ServerContext* context,
                const hybrid_scope::WgExecRequest& wg_exec,
                hybrid_scope::RpcResult* rpc_config) 
    {
        std::cout << wg_exec.id() << std::endl;
        return Status::OK;
    }
};


void run () 
{
    grpc::ServerBuilder builder;
    //添加端口和地址，不认证
    builder.AddListeningPort("localhost:12345",grpc::InsecureServerCredentials());

    //注册服务
    wgserver service;
    builder.RegisterService(&service);
    // 构建服务器
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server running " << std::endl;
    server->Wait(); 
}


int main (void) 
{
    run();
    return 0;
}






