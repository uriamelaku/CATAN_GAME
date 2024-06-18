#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#include <string>

enum class DevelopmentCardType {
    KNIGHT, //this card role is to move the robber and steal a resource from a player
    VICTORY_POINT, //this card role is to give you one victory point
    ROAD_BUILDING, //this card role is to build two roads
    YEAR_OF_PLENTY, //this card role is to take two resources of your choice from the bank
    MONOPOLY //this card role is to take all of a certain resource from all players 
};

class DevelopmentCard {
public:
    DevelopmentCardType type;

    DevelopmentCard(DevelopmentCardType cardType);
    std::string getTypeString() const;
};

#endif // DEVELOPMENTCARD_HPP
