#include "Player.hpp"

Player::Player(int playerId) : id(playerId), settlements(0), cities(0), roads(0), roadCount(2), settlementCount(2), cityCount(0) {
    resources[ResourceType::WOOD] = 0;
    resources[ResourceType::BRICK] = 0;
    resources[ResourceType::SHEEP] = 0;
    resources[ResourceType::WHEAT] = 0;
    resources[ResourceType::ORE] = 0;
}

void Player::addDevelopmentCard(const DevelopmentCard& card) {
    developmentCards.push_back(card);
}

bool Player::hasResources(const std::unordered_map<ResourceType, int>& cost) const {
    for (const auto& [type, amount] : cost) {
        if (resources.at(type) < amount) {
            return false;
        }
    }
    return true;
}

void Player::spendResources(const std::unordered_map<ResourceType, int>& cost) {
    for (const auto& [type, amount] : cost) {
        resources[type] -= amount;
    }
}

void Player::gainResources(ResourceType type, int amount) {
    resources[type] += amount;
}
