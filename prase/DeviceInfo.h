/**
 * @author zouxiaoliang
 * @date 2022/11/07
 */

#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <nlohmann/json.hpp>

namespace hybrid_scope {
namespace core {

struct DeviceInfo {
    std::uint32_t device_id{0};
    std::string device_uuid;

    friend void to_json(nlohmann::json& v, const DeviceInfo& self) {
        v["device_id"] = self.device_id;
        v["device_uuid"] = self.device_uuid;
    }

    friend void from_json(const nlohmann::json& v, DeviceInfo& self) {
        if (v.contains("device_id")) {
            v.at("device_id").get_to(self.device_id);
        }
        if (v.contains("device_uuid")) {
            v.at("device_uuid").get_to(self.device_uuid);
        }
    }
};

}
}

#endif // DEVICEINFO_H