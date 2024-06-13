#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "DevelopmentCard.hpp"
#include <vector>

class Player {
public:
    int id;
    int settlements;     // מספר היישובים על הלוח
    int cities;          // מספר הערים על הלוח
    int roads;           // מספר הדרכים על הלוח
    int roadCount;       // מספר הדרכים שנותרו לשחקן לבנות
    int settlementCount; // מספר היישובים שנותרו לשחקן לבנות
    int cityCount;       // מספר הערים שנותרו לשחקן לבנות
    std::vector<DevelopmentCard> developmentCards;

    Player(int id);
    
    void addDevelopmentCard(const DevelopmentCard& card);
};

#endif // PLAYER_HPP
