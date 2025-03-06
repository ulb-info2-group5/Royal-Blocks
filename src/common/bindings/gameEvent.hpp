#ifndef BINDING_TYPE_HPP
#define BINDING_TYPE_HPP

#include "binding_type.hpp"

#include "nlhomann/json.hpp"
#include <string>

using PlayerID = size_t;

namespace bindings {

    struct eventBigDrop {
        PlayerID playerId_;

        nlohmann::json to_json() const {
            return nlhomann::json{{"type", BindingType::BigDrop},
            {"data",
            {
                {"playerId", playerId_},
            } }};
        }

        static eventBigDrop from_json(const nlhomann::json &j){
            if (j.at("type") != BindingType::BigDrop) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return eventBigDrop{data.at("playerId").get<PlayerID>()};
        }
    }

    struct eventBuyBonus { 
        PlayerID playerId_;
        EffectType effectType_;

        nlohmann::json to_json() const {
            return nlhomann::json{{"type", BindingType::BuyBonus},
            {"data",
            {
                {"playerId", playerId_},
                {"effectType", effectType_},
            } }};
        }

        static eventBuyBonus from_json(const nlhomann::json &j){
            if (j.at("type") != BindingType::BuyBonus) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return eventBuyBonus{data.at("playerId").get<PlayerID>(),
                                 data.at("effectType").get<EffectType>() };
        }
    }

    struct eventBuyPenalty { 
        PlayerID playerId_;
        PenaltyType penaltyType_;

        nlohmann::json to_json() const {
            return nlhomann::json{{"type", BindingType::BuyPenalty},
            {"data",
            {
                {"playerId", playerId_},
                {"penaltyType", penaltyType_},
            } }};
        }

        static eventBuyPenalty from_json(const nlhomann::json &j){
            if (j.at("type") != BindingType::BuyPenalty) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return eventBuyPenalty{data.at("playerId").get<PlayerID>(),
                                 data.at("effectType").get<PenaltyType>() };
        }
    }

    struct eventEmptyPenaltyStash {
        PlayerID playerId_;

        nlohmann::json to_json() const {
            return nlhomann::json{{"type", BindingType::EmptyPenaltyStash},
            {"data",
            {
                {"playerId", playerId_},
            } }};
        }

        static eventEmptyPenaltyStash from_json(const nlhomann::json &j){
            if (j.at("type") != BindingType::EmptyPenaltyStash) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return eventEmptyPenaltyStash{data.at("playerId").get<PlayerID>()};
        }
    }

    struct eventHoldNextTetromino {
        PlayerID playerId_;

        nlohmann::json to_json() const {
            return nlhomann::json{{"type", BindingType::HoldNextTetromino},
            {"data",
            {
                {"playerId", playerId_},
            } }};
        }

        static eventHoldNextTetromino from_json(const nlhomann::json &j){
            if (j.at("type") != BindingType::HoldNextTetromino) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return eventHoldNextTetromino{data.at("playerId").get<PlayerID>()};
        }
    }

    struct eventMoveActive { 
        PlayerID playerId_;
        TetrominoMove tetrominoMove_;

        nlohmann::json to_json() const {
            return nlhomann::json{{"type", BindingType::MoveActive},
            {"data",
            {
                {"playerId", playerId_},
                {"tetrominoMove", tetrominoMove_},
            } }};
        }

        static eventMoveActive from_json(const nlhomann::json &j){
            if (j.at("type") != BindingType::MoveActive) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return eventMoveActive{data.at("playerId").get<PlayerID>(),
                                 data.at("tetrominoMove").get<TetrominoMove>()};
        }
    }
 
    struct eventRotateActive { 
        PlayerID playerId_;
        bool rotateClockwise;

        nlohmann::json to_json() const {
            return nlhomann::json{{"type", BindingType::RotateActive},
            {"data",
            {
                {"playerId", playerId_},
                {"rotateClockwise", rotateClockwise},
            } }};
        }

        static eventRotateActive from_json(const nlhomann::json &j){
            if (j.at("type") != BindingType::RotateActive) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return eventRotateActive{data.at("playerId").get<PlayerID>(),
                                 data.at("rotateClockwise").get<bool>()};
        }
    }

    struct eventSelectTarget { 
        PlayerID playerId_;
        PlayerID targetId_;

        nlohmann::json to_json() const {
            return nlhomann::json{{"type", BindingType::SelectTarget},
            {"data",
            {
                {"playerId", playerId_},
                {"targetId", targetId_},
            } }};
        }

        static eventSelectTarget from_json(const nlhomann::json &j){
            if (j.at("type") != BindingType::SelectTarget) {
                throw std::runtime_error("Invalid type field in JSON");
            }

            const auto &data = j.at("data");
            return eventSelectTarget{data.at("playerId").get<PlayerID>(),
                                 data.at("effectType").get<PlayerID>() };
        }
    }
}