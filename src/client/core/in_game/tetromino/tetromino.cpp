#include "tetromino.hpp"
#include "nlohmann/json_fwd.hpp"

void client::Tetromino::deserialize(const nlohmann::json &j) {
    anchorPoint.deserialize(j.at("anchorPoint"));
    colorId = j.at("colorId");

    body.clear();
    for (const auto &item : j.at("body")) {
        Vec2 v;
        v.deserialize(item);
        body.push_back(v);
    }
}
