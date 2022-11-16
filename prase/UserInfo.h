/**
 * @author zouxiaoliang
 * @date 2022/11/07
 */

#ifndef USERINFO_H
#define USERINFO_H

#include <nlohmann/json.hpp>

namespace hybrid_scope {
namespace core {

struct UserInfo {
    std::string token;
    std::uint32_t user_id{0};
    std::uint32_t org_id{0};
    std::string tenant_name;

    friend void to_json(nlohmann::json& v, const UserInfo& self) {
        v["token"] = self.token;
        v["user_id"] = self.user_id;
        v["org_id"] = self.org_id;
        v["tenant_name"] = self.tenant_name;
    }

    friend void from_json(const nlohmann::json& v, UserInfo& self) {
        if (v.contains("token")) {
            v.at("token").get_to(self.token);
        }
        if (v.contains("user_id")) {
            v.at("user_id").get_to(self.user_id);
        }
        if (v.contains("org_id")) {
            v.at("org_id").get_to(self.org_id);
        }
        if (v.contains("tenant_name")) {
            v.at("tenant_name").get_to(self.tenant_name);
        }
    }
};

} // namespace core
} // namespace hybrid_scope
#endif // USERINFO_H