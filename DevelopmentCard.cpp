//ooriamelaku@gmail.com
//208734889
#include "DevelopmentCard.hpp"
#include <string>

using namespace std;

DevelopmentCard::DevelopmentCard(DevelopmentCardType cardType) : type(cardType) {}

string DevelopmentCard::getTypeString() const {
    switch (type) {
        case DevelopmentCardType::KNIGHT: return "Knight";
        case DevelopmentCardType::VICTORY_POINT: return "Victory Point";
        case DevelopmentCardType::ROAD_BUILDING: return "Road Building";
        case DevelopmentCardType::YEAR_OF_PLENTY: return "Year of Plenty"; 
        case DevelopmentCardType::MONOPOLY: return "Monopoly";
    }
    return "Unknown";
}
