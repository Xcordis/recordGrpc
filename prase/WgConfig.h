/**
 * @author zouxiaoliang
 * @date 2022/11/07
 */

#ifndef WGCONFIG_H
#define WGCONFIG_H

#include "DeviceInfo.h"
#include "UserInfo.h"
// #include <nlohmann/json.hpp>
// #include"nlohmann/json.hpp"
#include <nlohmann/json.hpp>
#include <iostream>

namespace hybrid_scope {
namespace core {

struct WgPeer {
    std::string pubkey;
    std::string prikey;
    std::string ipv4;
    std::string ipv6;
    std::uint16_t port{0};
    std::string mask;

    friend void to_json(nlohmann::json& v, const WgPeer& self) {
        v["pubkey"] = self.pubkey;
        v["prikey"] = self.prikey;
        v["ipv4"] = self.ipv4;
        v["ipv6"] = self.ipv6;
        v["port"] = self.port;
        v["mask"] = self.mask;
    }

    friend void from_json(const nlohmann::json& v, WgPeer& self) {
        if (v.contains("pubkey")) {
            v.at("pubkey").get_to(self.pubkey);
        }
        if (v.contains("prikey")) {
            v.at("prikey").get_to(self.prikey);
        }
        if (v.contains("ipv4")) {
            v.at("ipv4").get_to(self.ipv4);
        }
        if (v.contains("ipv6")) {
            v.at("ipv6").get_to(self.ipv6);
        }
        if (v.contains("port")) {
            v.at("port").get_to(self.port);
        }
        if (v.contains("mask")) {
            v.at("mask").get_to(self.mask);
        }
    }
};

struct WgGateway {
    std::uint64_t id{0};
    std::string ip;
    std::uint16_t wireguard_port{0};
    std::string name;
    std::uint64_t gateway_id{0};
    std::string gateway_uuid;
    std::string gateway_public_key;
    std::uint64_t obf_key{0};
    std::uint32_t keep_alive{0};
    std::string transport;
    std::uint32_t mode{0};
    std::uint32_t encrypt_mode{0};
    std::string virtual_ipv4;
    std::string virtual_ipv6;
    std::uint32_t mtu{0};

    friend void to_json(nlohmann::json& v, const WgGateway& self) {
        v["id"] = self.id;
        v["ip"] = self.ip;
        v["wireguard_port"] = self.wireguard_port;
        v["name"] = self.name;
        v["gateway_id"] = self.gateway_id;
        v["gateway_uuid"] = self.gateway_uuid;
        v["gateway_public_key"] = self.gateway_public_key;
        v["obf_key"] = self.obf_key;
        v["keep_alive"] = self.keep_alive;
        v["transport"] = self.transport;
        v["mode"] = self.mode;
        v["encrypt_mode"] = self.encrypt_mode;
        v["virtual_ipv4"] = self.virtual_ipv4;
        v["virtual_ipv6"] = self.virtual_ipv6;
        v["mtu"] = self.mtu;
    }

    friend void from_json(const nlohmann::json& v, WgGateway& self) {
        if (v.contains("id")) {
            v.at("id").get_to(self.id);
        }
        if (v.contains("ip")) { 
            v.at("ip").get_to(self.ip);
        }
        if (v.contains("wireguard_port")) {
            v.at("wireguard_port").get_to(self.wireguard_port);
        }
        if (v.contains("name")) {
            v.at("name").get_to(self.name);
        }
        if (v.contains("gateway_id")) {
            v.at("gateway_id").get_to(self.gateway_id);
        }
        if (v.contains("gateway_uuid")) {
            v.at("gateway_uuid").get_to(self.gateway_uuid);
        }
        if (v.contains("gateway_public_key")) {
            v.at("gateway_public_key").get_to(self.gateway_public_key);
        }
        if (v.contains("obf_key")) {
            v.at("obf_key").get_to(self.obf_key);
        }
        if (v.contains("keep_alive")) {
            v.at("keep_alive").get_to(self.keep_alive);
        }
        if (v.contains("transport")) {
            v.at("transport").get_to(self.transport);
        }
        if (v.contains("mode")) {
            v.at("mode").get_to(self.mode);
        }
        if (v.contains("encrypt_mode")) {
            v.at("encrypt_mode").get_to(self.encrypt_mode);
        }
        if (v.contains("virtual_ipv4")) {
            v.at("virtual_ipv4").get_to(self.virtual_ipv4);
        }
        if (v.contains("virtual_ipv6")) {
            v.at("virtual_ipv6").get_to(self.virtual_ipv6);
        }
        if (v.contains("mtu")) {
            v.at("mtu").get_to(self.mtu);
        }
    }
};

struct WgTunnel {
    std::uint32_t opt{0};

    std::vector<std::uint32_t> box_ids;

    UserInfo user_info;
    DeviceInfo device_info;

    WgPeer peer;
    std::vector<WgGateway> gateway;


    friend void to_json(nlohmann::json& v, const WgTunnel& self) {
        v["opt"] = self.opt;
        v["box_ids"] = self.box_ids;
        v["user_info"] = self.user_info;
        v["device_info"] = self.device_info;
        v["peer"] = self.peer;
        v["gateway"] = self.gateway;
    }

    friend void from_json(const nlohmann::json& v, WgTunnel& self) {
        // std::cout << "from_json" << std::endl;
        if (v.contains("opt")) {
            v.at("opt").get_to(self.opt);
        }
        if (v.contains("box_ids")) {
            v.at("box_ids").get_to(self.box_ids);
        }
        if (v.contains("user_info")) {
            v.at("user_info").get_to(self.user_info);
        }
        if (v.contains("device_info")) {
            v.at("device_info").get_to(self.device_info);
        }
        if (v.contains("peer")) {
            v.at("peer").get_to(self.peer);
        }
        // std::cout << "from_json" << std::endl;
        if (v.contains("gateway")) {
            v.at("gateway").get_to(self.gateway);
            // std::cout << "from_json" << std::endl;
        }
    }
};

} // namespace core
} // namespace hybrid_scope

#endif // WGCONFIG_H