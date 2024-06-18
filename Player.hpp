#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "DevelopmentCard.hpp"
#include <vector>
#include <unordered_map>
#include "ResourceType.hpp"


class Player {
public:
    int id;
    int settlements;   
    int cities;          
    int roads;          
    int roadCount;       
    int settlementCount;
    int cityCount;
    int victoryPoints;  // number of victory points
    int knightsPlayed;   // number of knights played
    bool hasLongestRoad; // is the player has the longest road
    bool hasLargestArmy; // is the player has the largest army      
    std::vector<DevelopmentCard> developmentCards;
    std::unordered_map<ResourceType, int> resources; // map of resource type to amount

    Player(int id);
    
    void addDevelopmentCard(const DevelopmentCard& card);
    bool hasResources(const std::unordered_map<ResourceType, int>& cost) const;
    void spendResources(const std::unordered_map<ResourceType, int>& cost);
    void gainResources(ResourceType type, int amount);
    bool tradeWithBank(ResourceType giveResource, ResourceType getResource);
    void updateVictoryPoints();
    std::string DevelopmentCardTypeToString(DevelopmentCardType type) const;
};

#endif // PLAYER_HPP
