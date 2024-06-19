#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <unordered_map>
#include <array>
#include <map>
#include "HexTile.hpp"
#include "Corner.hpp"
#include "Edge.hpp"
#include "DevelopmentCard.hpp"
#include "DevelopmentCardDeck.hpp"
#include "Player.hpp"
#include "ResourceType.hpp"
#include <unordered_set>

class Board {
private:
    std::vector<HexTile> tiles;
    std::unordered_map<int, Corner> corners;
    std::unordered_map<int, Edge> edges;
    DevelopmentCardDeck developmentDeck;
    std::vector<Player> players;
    

    void initializeTile(int index, ResourceType type, int number);
    void initializeConnections();

public:
    
    Board();
    void initialize();
    void printBoard() const;
    void printPlayerStatus(int playerId) const;
    void printAllPlayersStatus() const;

    // for testing purposes
    void addAlotOfResourcesAndCards();


    bool addSettlement(int cornerId, int playerId);
    bool upgradeSettlement(int cornerId, int playerId);
    bool addRoad(int edgeId, int playerId);
    DevelopmentCard drawDevelopmentCard(int playerId);
    void processCommand(const std::string& command, int playerId, bool& validMove); 
    int rollDice() const;

    bool canUpgradeSettlement(int cornerId, int playerId) const;

    void addPlayer(int playerId);

    bool canBuildSettlement(int cornerId, int playerId) const;
    bool canBuildRoad(int edgeId, int playerId) const;
    void distributeResources(int diceRoll);
    void processCommandWithBankTrade(const std::string& command, int playerId);
    ResourceType stringToResourceType(const std::string& resourceStr) const;
    void handleRobber();
    void moveRobber(int tileId);

    void checkLongestRoad();
    int calculateLongestRoad(int playerId) const;
    void checkLargestArmy();
    void endGame(int winnerId, int maxPoints) const;

    int dfsFindLongestRoad(int edgeId, int playerId, std::unordered_set<int>& visited) const;
    std::vector<int> getConnectedEdges(int edgeId) const;

    void playRoadBuilding(int playerId);
    void playYearOfPlenty(int playerId, ResourceType resourceType1, ResourceType resourceType2);
    void playMonopoly(int playerId, ResourceType resourceType);



};

#endif // BOARD_HPP
