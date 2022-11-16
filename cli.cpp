
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
using json =  nlohmann::json;

class Wgcontrol {
public:
    Wgcontrol(std::shared_ptr<grpc::Channel> channel):m_stub(hybrid_scope::Wg::NewStub(channel)) {}
    ~Wgcontrol(){}
    Status wg_exec(const json& m_json)
    {
        hybrid_scope::WgExecRequest wg_exec;
        hybrid_scope::RpcResult rpc_sult;
        hybrid_scope::core::WgTunnel wg_tunnel;
        ClientContext cli_context;
        wg_tunnel = m_json;
        wg_exec.set_id(1);
        wg_exec.set_cmdline("tian hei l");
        return m_stub->exec(&cli_context,wg_exec,&rpc_sult);
    }
    Status wg_up(const json& m_json)
    {   
        hybrid_scope::WgStartupRequest wg_start_up;
        hybrid_scope::RpcResult rpc_sult;
        wg_start_up.set_id(1);
        ClientContext cli_context;
        return m_stub->startup(&cli_context,wg_start_up,&rpc_sult);
    }
    Status wg_down(const json& m_json)
    {
        
        hybrid_scope::WgShutdownRequest wg_shut_down;
        hybrid_scope::RpcResult rpc_sult;
        wg_shut_down.set_id(1);
        ClientContext cli_context;
        return m_stub->shutdown(&cli_context,wg_shut_down,&rpc_sult);
    }
    Status wg_config(const json& m_json)
    {

        hybrid_scope::core::WgTunnel wg_tunnel;
        hybrid_scope::WgConfigRequest wg_request;
        hybrid_scope::RpcResult rpc_result;
        ClientContext context;
        wg_tunnel = m_json;
        wg_request.set_opt(wg_tunnel.opt);
        //单次连接
        auto j=wg_request.mutable_device_info();  
        j->set_device_id(wg_tunnel.device_info.device_id);
        j->set_device_uuid(wg_tunnel.device_info.device_uuid);
        // 二级链接
        auto a = wg_request.add_tunnels()->mutable_gateway_info();
        auto b = wg_request.add_tunnels()->mutable_peer_info();
        a->set_ip(wg_tunnel.gateway.front().ip);
        a->set_mtu(wg_tunnel.gateway.front().mtu);
        a->set_mode(wg_tunnel.gateway.front().mode);
        a->set_keep_alive(wg_tunnel.gateway.front().keep_alive);
        a->set_id(wg_tunnel.gateway.front().id);
        a->set_gateway_uuid(wg_tunnel.gateway.front().gateway_uuid);
        a->set_gateway_public_key(wg_tunnel.gateway.front().gateway_public_key);
        a->set_gateway_id(wg_tunnel.gateway.front().gateway_id);
        a->set_name(wg_tunnel.gateway.front().name);
        
        std::cout << "ok " << a->ip()<< std::endl;
        return m_stub->sync_config(&context,wg_request,&rpc_result);
    }
private:
    std::shared_ptr<hybrid_scope::Wg::Stub> m_stub;
};

void run () 
{
    Wgcontrol wg_con( grpc::CreateChannel("localhost:12345", grpc::InsecureChannelCredentials()));
    std::string path = "/home/cony/coding/cliApi/json/info.json";
    std::ifstream jfile(path);
    if(!jfile.is_open()) return;
    json m_json;
    jfile >> m_json;
    Status OK = wg_con.wg_config(m_json);
    if(OK.ok()) {
        std::cout << "ok" << std::endl;
    }
}


int main (void) {
    run();
    return 0;
}