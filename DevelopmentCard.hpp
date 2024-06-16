#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#include <string>

enum class DevelopmentCardType {
    KNIGHT,
    VICTORY_POINT,
    ROAD_BUILDING,
    YEAR_OF_PLENTY,
    MONOPOLY
};

class DevelopmentCard {
public:
    DevelopmentCardType type;

    DevelopmentCard(DevelopmentCardType cardType);
    std::string getTypeString() const;
};

#endif // DEVELOPMENTCARD_HPP
