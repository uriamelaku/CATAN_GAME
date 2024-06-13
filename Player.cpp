#include "Player.hpp"

Player::Player(int playerId) : id(playerId), settlements(2), cities(0), roads(2) {}

void Player::addDevelopmentCard(const DevelopmentCard& card) {
    developmentCards.push_back(card);
}
