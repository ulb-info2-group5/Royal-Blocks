#include "tetromino.hpp"

nlohmann::json client::Tetromino::serialize() const {
    nlohmann::json j_body = nlohmann::json::array();
    for (const auto &vec : body_) {
        j_body.push_back(vec.serialize());
    }

    return nlohmann::json{{"anchorPoint", anchorPoint_.serialize()},
                          {"body", j_body}};
}

void client::Tetromino::deserialize(const nlohmann::json &j) {
    anchorPoint_.deserialize(j.at("anchorPoint"));

    body_.clear();
    for (const auto &item : j.at("body")) {
        Vec2 v;
        v.deserialize(item);
        body_.push_back(v);
    }
}
