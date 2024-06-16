#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "DevelopmentCard.hpp"
#include <vector>
#include <unordered_map>
#include "ResourceType.hpp"

//enum class ResourceType { WOOD, BRICK, SHEEP, WHEAT, ORE, NONE };

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
    std::unordered_map<ResourceType, int> resources; // משאבים שיש לשחקן

    Player(int id);
    
    void addDevelopmentCard(const DevelopmentCard& card);
    bool hasResources(const std::unordered_map<ResourceType, int>& cost) const;
    void spendResources(const std::unordered_map<ResourceType, int>& cost);
    void gainResources(ResourceType type, int amount);
};

#endif // PLAYER_HPP
