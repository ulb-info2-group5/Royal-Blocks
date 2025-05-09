#include "tetromino.hpp"

#include <map>
#include <nlohmann/detail/iterators/iter_impl.hpp>
#include <nlohmann/json.hpp>

#include "vec2/vec2.hpp"

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
