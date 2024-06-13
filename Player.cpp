#include "Player.hpp"

Player::Player(int playerId) : id(playerId), settlements(0), cities(0), roads(0), roadCount(2), settlementCount(1), cityCount(0) {}

void Player::addDevelopmentCard(const DevelopmentCard& card) {
    developmentCards.push_back(card);
}
