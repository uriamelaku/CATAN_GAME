#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include "DevelopmentCard.hpp"

class Player {
public:
    int id;
    int settlements;
    int cities;
    int roads;
    std::vector<DevelopmentCard> developmentCards;

    Player(int playerId);
    void addDevelopmentCard(const DevelopmentCard& card);
};

#endif // PLAYER_HPP
