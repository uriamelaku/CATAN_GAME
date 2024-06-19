#include "Board.hpp"
#include <iostream>
#include <sstream>
#include <map>
#include <array>
#include <cstdlib>
#include <algorithm>
#include <unordered_set>



using namespace std;

Board::Board() {
    tiles.resize(19);
}

    void Board::initialize() {
        // אתחול אריחים
        initializeTile(0, ResourceType::MOUNTAIN, 10);
        initializeTile(1, ResourceType::FIELD, 2);
        initializeTile(2, ResourceType::FOREST, 9);
        initializeTile(3, ResourceType::PASTURE, 12);
        initializeTile(4, ResourceType::HILL, 6);
        initializeTile(5, ResourceType::FIELD, 4);
        initializeTile(6, ResourceType::HILL, 10);
        initializeTile(7, ResourceType::PASTURE, 9);
        initializeTile(8, ResourceType::FOREST, 11);
        initializeTile(9, ResourceType::DESERT, 0); /////// this is the desert tile, to chane the num
        initializeTile(10, ResourceType::FOREST, 3);
        initializeTile(11, ResourceType::MOUNTAIN, 8);
        initializeTile(12, ResourceType::FOREST, 8);
        initializeTile(13, ResourceType::MOUNTAIN, 3);
        initializeTile(14, ResourceType::PASTURE, 4);
        initializeTile(15, ResourceType::FIELD, 5);
        initializeTile(16, ResourceType::HILL, 5);
        initializeTile(17, ResourceType::PASTURE, 6);
        initializeTile(18, ResourceType::FIELD, 11);

        // אתחול פינות וקווים לפי טבלה קבועה
        initializeConnections();
    }

    void Board::initializeTile(int index, ResourceType type, int number) {
        tiles[index] = HexTile(type, number);
    }

    void Board::initializeConnections() {
        // set the connections between corners and edges
        static const std::array<std::array<int, 6>, 19> cornerConnections = {{
            {0, 1, 2, 3, 4, 5},      // 
            {6, 7, 8, 9, 2, 1},      // 
            {10, 11, 12, 13, 8, 7},  // 
            {4, 3, 14, 15, 16, 17},   // 
            {2, 9, 18, 19, 14, 3},  //  4
            {8, 13, 20, 21, 18, 9}, //  5
            {12, 22, 23, 24, 20, 13}, //  6
            {16, 15, 25, 26, 27, 28},  //  7
            {14, 19, 29, 30, 25, 15}, //  8
            {18, 21, 31, 32, 29, 19}, //  9
            {20, 24, 33, 34, 31, 21}, //  10
            {23, 35, 36, 37, 33, 24}, //  11
            {25, 30, 40, 39, 38, 26}, //  12
            {29, 32, 42, 41, 40, 30}, //  13
            {31, 34, 44, 43, 42, 32}, //  14
            {33, 37, 46, 45, 44, 34}, //  15
            {40, 41, 49, 48, 47, 39}, //  16
            {42, 43, 51, 50, 49, 41}, //  17
            {44, 45, 53, 52, 51, 43}, //  18
        }};

        static const std::array<std::array<int, 6>, 19> edgeConnections = {{
            {1, 2, 3, 4, 5, 6},      //  0
            {7, 8, 9, 10, 2, 11},     //  1
            {12, 13, 14, 15, 8, 16}, //  2
            {4, 17, 18, 19, 20, 21},   //  3
            {10, 22, 23, 24, 17, 3},  //  4
            {15, 25, 26, 27, 22, 9},//  5
            {28, 29, 30, 31, 25, 14},//  6
            {19, 32, 33, 34, 35, 36}, //  7
            {24, 37, 38, 39, 32, 18},//  8
            {27, 40, 41, 42, 37, 23},//  9
            {31, 43, 44, 45, 40, 26},//  10
            {46, 47, 48, 49, 43, 30},//  11
            {39, 50, 51, 52, 53, 33},//  12
            {42, 54, 55, 56, 50, 38},//  13
            {45, 57, 58, 59, 54, 41},//  14
            {49, 60, 61, 62, 57, 44},//  15
            {56, 63, 64, 65, 66, 51},//  16
            {59, 67, 68, 69, 63, 55},//  17
            {62, 70, 71, 72, 67, 58},//  18
        }};

        // iterate over all tiles and set the connections between corners and edges   
        for (size_t i = 0; i < tiles.size(); ++i) {
            for (int j = 0; j < 6; ++j) {
                int cornerId = cornerConnections[i][j];
                if (corners.find(cornerId) == corners.end()) {
                    corners[cornerId] = Corner();
                }
                tiles[i].corners[j] = cornerId;

                int edgeId = edgeConnections[i][j];
                if (edges.find(edgeId) == edges.end()) {
                    edges[edgeId] = Edge();
                }
                tiles[i].edges[j] = edgeId;
            }
        }
        
    }



void Board::printBoard() const {
    std::cout << std::endl << "                     ********** CATAN BOARD **********" << std::endl;

    const std::array<std::array<int, 7>, 7> layout = {{
        {-1, -1, -1, -1, -1, -1, -1},
        {-1, -1,  0,  1,  2, -1, -1},
        {-1,  3,  4,  5,  6, -1, -1},
        { 7,  8,  9, 10, 11, -1, -1},
        {-1, 12, 13, 14, 15, -1, -1},
        {-1, -1, 16, 17, 18, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1}
    }};

    auto getTileRepresentation = [&](int tileIndex) -> std::string {
        if (tileIndex == -1) {
            return "  ---   ";
        }
        const HexTile& tile = tiles[tileIndex];
        std::string resource = tile.getTypeString();
        std::string number = std::to_string(tile.getNumber());
        return " " + resource + " " + number + " ";
    };

    for (size_t i = 0; i < layout.size(); ++i) {
        std::string rowStr =  "";
        if(i == 2){
            rowStr += "       ";
        }
        if(i == 3){
            rowStr += "        ";
        }
        if(i == 4){
            rowStr += "          ";
        }
        if(i == 5){
            rowStr += "    ";
        }
        for (int tileIndex : layout[i]) {
            rowStr += getTileRepresentation(tileIndex) + " ";
        }
        if (i % 2 == 1) {
            std::cout << std::endl << "  " << rowStr << std::endl; // Add spacing for odd rows to align hexagons
        } else {
            std::cout << std::endl << rowStr << std::endl;
        }
    }

    std::cout << std::endl << "                     **********************************" << std::endl;

    
    
}

void Board::addAlotOfResourcesAndCards(){

   
        for(auto& player : players){
            player.gainResources(ResourceType::BRICK, 10);
            player.gainResources(ResourceType::WOOD, 10);
            player.gainResources(ResourceType::WOOL, 10);
            player.gainResources(ResourceType::WHEAT, 10);
            player.gainResources(ResourceType::IRON, 10);
            // add development cards to each player
            for(int i = 0; i < 3; i++){
                player.addDevelopmentCard(DevelopmentCard(DevelopmentCardType::KNIGHT));
                player.addDevelopmentCard(DevelopmentCard(DevelopmentCardType::MONOPOLY));
                player.addDevelopmentCard(DevelopmentCard(DevelopmentCardType::ROAD_BUILDING));
                //player.addDevelopmentCard(DevelopmentCard(DevelopmentCardType::VICTORY_POINT));
                player.addDevelopmentCard(DevelopmentCard(DevelopmentCardType::YEAR_OF_PLENTY));
            }
        }
    
}

bool Board::canBuildSettlement(int cornerId, int playerId) const {
    if (corners.at(cornerId).building != BuildingType::NONE) {
        return false; // the corner is already occupied
    }

    // check if the corner is connected to a road
    for (const auto& tile : tiles) {
        if (std::find(tile.corners.begin(), tile.corners.end(), cornerId) != tile.corners.end()) {
            for (const auto& adjacentCorner : tile.corners) {
                if (cornerId != adjacentCorner && corners.at(adjacentCorner).building != BuildingType::NONE) {
                    return false; // the corner is connected to a road    
                }
            }
        }
    }

    // check if the corner is connected to a settlement or city of the player
    for (const auto& tile : tiles) {
        if (std::find(tile.corners.begin(), tile.corners.end(), cornerId) != tile.corners.end()) {
            for (const auto& edge : tile.edges) {
                const auto& edgeTile = edges.at(edge);
                if (edgeTile.owner == playerId && edgeTile.road == RoadType::ROAD) {
                    return true; // the corner is connected to a road of the player 
                }
            }
        }
    }

    return false;
}

bool Board::canBuildRoad(int edgeId, int playerId) const {
    // check if the edge is already occupied
    if (edges.at(edgeId).road != RoadType::NONE) {
        return false;
    }
    // check if the edge is connected to a settlement or city of the player
    return true;
}

void Board::addPlayer(int playerId) {
    players.emplace_back(playerId);
}

int Board::rollDice() const {
    return (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
}

bool Board::addRoad(int edgeId, int playerId) {
    // cost of a road
    std::unordered_map<ResourceType, int> roadCost = {
        {ResourceType::BRICK, 1},
        {ResourceType::WOOD, 1}
    };

    // iterate over all players and check if the player has enough resources to build a road
    for (auto& player : players) {
        if (player.id == playerId) {
            // check if the player has any roads left
            if (player.roadCount != 0) {
                // check if the player can build a road at the edge
                if (canBuildRoad(edgeId, playerId)) {
                    // build a road at the edge
                    edges[edgeId].road = RoadType::ROAD;
                    edges[edgeId].owner = playerId;
                    player.roads++;
                    player.roadCount--;
                    return true;
                } else {
                    std::cout << "Cannot build road at edge " << edgeId << "." << std::endl;
                    return false;
                }
            } 
            // check if the player has enough resources to build a road
            else if (player.hasResources(roadCost) || player.roadCount != 0) {
                // check if the player can build a road at the edge
                if (canBuildRoad(edgeId, playerId)) {
                    // build a road at the edge
                    edges[edgeId].road = RoadType::ROAD;
                    edges[edgeId].owner = playerId;
                    player.roads++;
                    player.roadCount--;
                    player.spendResources(roadCost); // spend the resources to build a road
                    return true;
                } else {
                    std::cout << "Cannot build road at edge " << edgeId << "." << std::endl;
                    return false;
                }
            } 
            else {
                std::cout << "Player " << playerId << " does not have enough resources to build a road." << std::endl;
                return false;
            }
        }
    }

    std::cout << "Player " << playerId << " not found." << std::endl;
    return false;
}

bool Board::addSettlement(int cornerId, int playerId) {
    // cost of a settlement
    std::unordered_map<ResourceType, int> settlementCost = {
        {ResourceType::BRICK, 1},
        {ResourceType::WOOD, 1},
        {ResourceType::WOOL, 1},
        {ResourceType::WHEAT, 1}
    };

    // check if the corner is already occupied
    if (corners[cornerId].building != BuildingType::NONE) {
        std::cout << "Corner " << cornerId << " is already occupied." << std::endl;
        return false;
    }
    // check if the player can build a settlement at the corner
    if (!canBuildSettlement(cornerId, playerId)) {
        std::cout << "Cannot build settlement at corner " << cornerId << " according to game rules." << std::endl;
        return false;
    }

    // iterate over all players and check if the player has enough resources to build a settlement
    for (auto& player : players) {
        if (player.id == playerId) {
            // check if the player has any settlements left
            if (player.settlementCount != 0) {
                // build a settlement at the corner
                corners[cornerId].building = BuildingType::SETTLEMENT;
                corners[cornerId].owner = playerId;
                player.settlements++;
                player.settlementCount--;
                return true;
            } 
            // check if the player has enough resources to build a settlement
            else if (player.hasResources(settlementCost) || player.settlementCount != 0) {
                // build a settlement at the corner
                corners[cornerId].building = BuildingType::SETTLEMENT;
                corners[cornerId].owner = playerId;
                player.settlements++;
                player.settlementCount--;
                player.spendResources(settlementCost); // spend the resources to build a settlement
                return true;
            } 
            else {
                std::cout << "Player " << playerId << " does not have enough resources to build a settlement." << std::endl;
                return false;
            }
        }
    }

    std::cout << "Player " << playerId << " not found." << std::endl;
    return false;
}

bool Board::canUpgradeSettlement(int cornerId, int playerId) const {
    // check if the corner has a settlement
    if (corners.at(cornerId).building != BuildingType::SETTLEMENT) {
        return false;
    }
    // check if the corner belongs to the player
    if (corners.at(cornerId).owner != playerId) {
        return false;
    }
    return true;
}

// this function gives the resources to the players according to the dice roll
void Board::distributeResources(int diceRoll) {
    if (diceRoll == 7) {
        handleRobber();
    } 
    else {
        // iterate over all tiles and check if the number matches the dice roll
        for (const auto& tile : tiles) {
            // if the tile number matches the dice roll and the tile does not have the robber, give resources to the players
            if (tile.getNumber() == diceRoll && !tile.hasRobber) {
                for (const auto& cornerId : tile.corners) { // iterate over all corners of the tile
                    const auto& corner = corners.at(cornerId);
                    if (corner.building != BuildingType::NONE) { // check if the corner has a building
                        for (auto& player : players) {
                            if (player.id == corner.owner) {
                                // if the corner has a settlement, give 1 resource of the tile type, if it has a city, give 2 resources
                                ResourceType type;
                                if(tile.type == ResourceType::FOREST){
                                    type = ResourceType::WOOD;
                                }
                                if(tile.type == ResourceType::PASTURE){
                                    type = ResourceType::WHEAT;
                                }
                                if(tile.type == ResourceType::FIELD){
                                    type = ResourceType::WOOL;
                                }
                                if(tile.type == ResourceType::MOUNTAIN){
                                    type = ResourceType::IRON;
                                }
                                if(tile.type == ResourceType::HILL){
                                    type = ResourceType::BRICK;
                                }
                                if(tile.type == ResourceType::DESERT){
                                    type = ResourceType::NONE;
                                }
                                if(type != ResourceType::NONE){
                                    player.gainResources(type, (corner.building == BuildingType::CITY) ? 2 : 1);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void Board::moveRobber(int newTileId) {
    for (auto& tile : tiles) {
        tile.hasRobber = false; // Remove the robber from the current tile
    }
    tiles[newTileId].hasRobber = true; // Place the robber on the new tile
    std::cout << "The robber has been moved to tile " << newTileId << ".\n";
}

void Board::handleRobber() {
    std::cout << "A 7 was rolled! The robber is activated.\n";
    
    // Handle the case where players with more than 7 resources must discard half of their resources
    for (auto& player : players) {
        int totalResources = 0;
        for (const auto& resource : player.resources) {
            totalResources += resource.second;
        }
        if (totalResources > 7) {
            std::cout << "Player " << player.id << " has more than 7 resources and must discard half.\n";
            // Logic for discarding half the resources
            for (auto& resource : player.resources) {
                resource.second /= 2; // Discard half of each resource
            }
        }
    }
    
    // Move the robber to a new tile
    int newTileId;
    std::cout << "Enter the ID of the tile to move the robber to: ";
    std::cin >> newTileId;
    moveRobber(newTileId);
}

bool Board::upgradeSettlement(int cornerId, int playerId) {
    std::unordered_map<ResourceType, int> cityCost = { // cost of a city
        {ResourceType::IRON, 3},
        {ResourceType::WHEAT, 2}
    };

    for (auto& player : players) { // iterate over all players
        if (player.id == playerId) {
            if (player.cityCount > 0) { // check if the player has a city to place
                if (canUpgradeSettlement(cornerId, playerId)) { // check if there is a settlement at the corner
                    corners[cornerId].building = BuildingType::CITY; // upgrade the settlement to a city
                    player.cities++;
                    player.settlements--;
                    player.cityCount--;
                    return true;
                } else {
                    std::cout << "Cannot upgrade settlement at corner " << cornerId << "." << std::endl;
                    return false;
                }
            } else if (player.hasResources(cityCost)) { // check if the player has enough resources to buy a city
                if (canUpgradeSettlement(cornerId, playerId)) { // check if there is a settlement at the corner
                    corners[cornerId].building = BuildingType::CITY; // upgrade the settlement to a city
                    player.cities++;
                    player.settlements--;
                    player.cityCount--;
                    player.spendResources(cityCost); // spend the resources to buy a city
                    return true;
                } else {
                    std::cout << "Cannot upgrade settlement at corner " << cornerId << "." << std::endl;
                    return false;
                }
            } else {
                std::cout << "Player " << playerId << " does not have enough resources to buy a city." << std::endl;
                return false;
            }
        }
    }
    std::cout << "Player " << playerId << " not found." << std::endl;
    return false;
}

void Board::printPlayerStatus(int playerId) const {
    for (const auto& player : players) {
        if (player.id == playerId) {
            std::cout << "Player " << player.id << " Status:" << std::endl;
            std::cout << "  Settlements: " << player.settlements << std::endl;
            std::cout << "  Cities: " << player.cities << std::endl;
            std::cout << "  Roads: " << player.roads << std::endl;
            std::cout << "  Remaining Settlements: " << player.settlementCount << std::endl;
            std::cout << "  Remaining Cities: " << player.cityCount << std::endl;
            std::cout << "  Remaining Roads: " << player.roadCount << std::endl;

            // Print the amount of development cards
            std::cout << "  Development Cards Amount: " << player.developmentCards.size() << std::endl;

            // Print the types of development cards
            std::cout << "  Development Cards Type: ";
            for (const auto& card : player.developmentCards) {
                std::cout << player.DevelopmentCardTypeToString(card.type) << ", ";
            }
            std::cout << std::endl;

            // Print the resources
            std::cout << "  Resources:   ";
            for (const auto& resource : player.resources) {
                if (resource.first == ResourceType::DESERT) continue;
                std::cout << resourceTypeToString(resource.first) << ": " << resource.second << " ";
            }
            std::cout << std::endl;

            // Print the victory points
            std::cout << "  Points: " << player.victoryPoints << std::endl;
            std::cout << std::endl << std::endl;
            break;
        }
    }
}

void Board::printAllPlayersStatus() const {
    for (const auto& player : players) {
        printPlayerStatus(player.id);
        std::cout << std::endl; // Add spacing between players
    }
}




DevelopmentCard Board::drawDevelopmentCard(int playerId) {
    DevelopmentCard card = developmentDeck.drawCard();
    for (auto& player : players) {
        if (player.id == playerId) {
            player.addDevelopmentCard(card);
            break;
        }
    }
    return card;
}

ResourceType Board::stringToResourceType(const std::string& resourceStr) const {
    if (resourceStr == "wood") return ResourceType::WOOD;
    if (resourceStr == "brick") return ResourceType::BRICK;
    if (resourceStr == "wool") return ResourceType::WOOL;
    if (resourceStr == "wheat") return ResourceType::WHEAT;
    if (resourceStr == "iron") return ResourceType::IRON;
    return ResourceType::NONE;
}


void Board::processCommandWithBankTrade(const std::string& command, int playerId) {
    std::istringstream iss(command);
    std::string action, giveResourceStr, getResourceStr;
 
    iss >> action >> giveResourceStr >> getResourceStr;

    if (action != "trade_with_bank") {
        std::cout << "Invalid command for bank trade." << std::endl;
        return;
    }

    ResourceType giveResource = stringToResourceType(giveResourceStr);
    ResourceType getResource = stringToResourceType(getResourceStr);

    for (auto& player : players) {
        if (player.id == playerId) {
            if (player.tradeWithBank(giveResource, getResource)) {
                std::cout << "Player " << playerId << " traded 4 " << resourceTypeToString(giveResource) 
                          << " for 1 " << resourceTypeToString(getResource) << "." << std::endl;
            } else {
                std::cout << "Player " << playerId << " does not have enough " << resourceTypeToString(giveResource) << " to trade." << std::endl;
            }
            return;
        }
    }
    std::cout << "Player " << playerId << " not found." << std::endl;
}

void Board::processCommand(const std::string& command, int playerId, bool& validMove) {
    std::istringstream iss(command);
    std::string action;
    int id;

    iss >> action;

    validMove = false;

    // roll_dice command
    if (action == "1") {
        int result = rollDice();
        std::cout << "Player " << playerId << " rolled the dice: " << result << std::endl;
        distributeResources(result);
        validMove = true;
    } 
    // build_settlement, upgrade_settlement, build_road - commands
    else if (action == "3" || action == "4" || action == "2") {

        // if action is build_road, ask for edge ID
        std::cout << "Enter the " << (action == "2" ? "edge" : "corner") << " ID: ";
        std::cin >> id;
        std::cin.ignore(); // Ignore the newline character after the number
        
        if (action == "3") {
            if (addSettlement(id, playerId)) {
                std::cout << "Player " << playerId << " built a settlement at corner " << id << "." << std::endl;
                validMove = true;
            } 
            else {
                std::cout << "Failed to build settlement at corner " << id << "." << std::endl;
            }
        } 
        else if (action == "4") {
            if (upgradeSettlement(id, playerId)) {
                std::cout << "Player " << playerId << " upgraded a settlement to a city at corner " << id << "." << std::endl;
                validMove = true;
            } else {
                std::cout << "Failed to upgrade settlement at corner " << id << "." << std::endl;
            }
        } 
        else if (action == "2") {
            if (addRoad(id, playerId)) {
                std::cout << "Player " << playerId << " built a road at edge " << id << "." << std::endl;
                checkLongestRoad(); // check for longest road
                validMove = true;
            } else {
                std::cout << "Failed to build road at edge " << id << "." << std::endl;
            }
        }
    } 
    // draw_card command
    else if (action == "5") {
        // Define the cost of a development card
        std::unordered_map<ResourceType, int> developmentCardCost = {
            {ResourceType::IRON, 1},
            {ResourceType::WHEAT, 1},
            {ResourceType::WOOL, 1}
        };

        for (auto& player : players) {
            if (player.id == playerId) {
                if (player.hasResources(developmentCardCost)) {
                    player.spendResources(developmentCardCost);
                    DevelopmentCard card = drawDevelopmentCard(playerId);
                    std::cout << "Player " << playerId << " drew a development card: " << card.getTypeString() << std::endl;
                    validMove = true;
                } 
                else {
                    std::cout << "Player " << playerId << " does not have enough resources to buy a development card." << std::endl;
                }
                break;
            }
        }
    } 
    else if (action == "9") 
    {
        std::cout << "Enter the development card type:  (1.road building, 2.year of plenty, 3.monopoly)" << std::endl;
        std::string cardType;
        std::cin >> cardType;

        if (cardType == "1") {
            playRoadBuilding(playerId);
            validMove = true;
        } 
        else if (cardType == "2") {
            std::string resourceStr1, resourceStr2;
            std::cout << "Enter two resources to gain: (wood, brick, wool, wheat, iron)" << std::endl;
            std::cin >> resourceStr1 >> resourceStr2;
            ResourceType resourceType1 = stringToResourceType(resourceStr1);
            ResourceType resourceType2 = stringToResourceType(resourceStr2);
            playYearOfPlenty(playerId, resourceType1, resourceType2);
        } 
        else if (cardType == "3") {
            std::string resourceStr;
            std::cout << "Enter the resource to monopolize:  (wood, brick, wool, wheat, iron)" << std::endl;
            std::cin >> resourceStr;
            ResourceType resourceType = stringToResourceType(resourceStr);
            playMonopoly(playerId, resourceType);
        } 
        else {
            std::cout << "Invalid development card type." << std::endl;
        }
        validMove = true;
    } 
    else {
        std::cout << "nknown command." << std::endl;
    }


    // if the move was valid, print the updated board and player status
    if (validMove) {
        // check if the player has won the game
        for (auto& player : players) {
            // check if the player has won the game
            if (player.id == playerId) {
                player.updateVictoryPoints();
                if (player.victoryPoints >= 10) {
                    endGame(playerId, player.victoryPoints);
                    std::exit(0); // Exit the program when a player wins
                }
            }
        }
        // Update player status and board only if the move was valid
        printBoard();
        printPlayerStatus(playerId);
    }
}

void Board::checkLongestRoad() {
    int longestRoad = 0;
    int playerWithLongestRoad = -1;

    // iterate over all players and calculate the longest road for each player
    for (auto& player : players) {
        int roadLength = calculateLongestRoad(player.id);
        // if the road length is greater than 5 and greater than the current longest road, update the longest road
        if (roadLength >= 5 && roadLength > longestRoad) {
            longestRoad = roadLength;
            playerWithLongestRoad = player.id;
        }
    }

    // check if the player with the longest road has changed
    for (auto& player : players) {
        if (player.id == playerWithLongestRoad) { // if the player has the longest road
            player.hasLongestRoad = true;
        } 
        else { // if the player does not have the longest road
            player.hasLongestRoad = false; // set hasLongestRoad to false
        }
        player.updateVictoryPoints(); // update the player's victory points
    }
}


void Board::checkLargestArmy() {
    int maxKnights = 0;
    int playerWithLargestArmy = -1;

    // iterate over all players and find the player with the largest army
    for (auto& player : players) {
        // if the player has played more knights than the current maxKnights, update the maxKnights and playerWithLargestArmy
        if (player.knightsPlayed > maxKnights) {
            maxKnights = player.knightsPlayed;
            playerWithLargestArmy = player.id;
        }
    }

    // check if the player with the largest army has changed
    for (auto& player : players) {
        // if the player has the largest army, set hasLargestArmy to true, otherwise set it to false
        if (player.id == playerWithLargestArmy) {
            player.hasLargestArmy = true;
        } 
        else { // if the player does not have the largest army
            player.hasLargestArmy = false;
        }
        player.updateVictoryPoints();
    }
}

void Board::endGame(int winnerId, int maxPoints) const {
    std::cout << "The game has ended. The winner is player " << winnerId << " with " << maxPoints << " victory points!" << std::endl;
}


int Board::calculateLongestRoad(int playerId) const {
    int longestRoad = 0;

    // iterate over all edges to find the longest road for the player
    for (const auto& edge : edges) {
        if (edge.second.owner == playerId) {
            // use DFS or BFS to find the longest path from this edge
            std::unordered_set<int> visited;
            int roadLength = dfsFindLongestRoad(edge.first, playerId, visited);
            longestRoad = std::max(longestRoad, roadLength);
        }
    }

    return longestRoad;
}

int Board::dfsFindLongestRoad(int edgeId, int playerId, std::unordered_set<int>& visited) const {
    visited.insert(edgeId);
    int maxLength = 0;

    for (const auto& neighborEdgeId : getConnectedEdges(edgeId)) {
        if (edges.at(neighborEdgeId).owner == playerId && visited.find(neighborEdgeId) == visited.end()) {
            maxLength = std::max(maxLength, dfsFindLongestRoad(neighborEdgeId, playerId, visited));
        }
    }

    visited.erase(edgeId);
    return maxLength + 1;
}

std::vector<int> Board::getConnectedEdges(int edgeId) const {
    std::vector<int> connectedEdges;
    for (const auto& tile : tiles) {
        for (const auto& edge : tile.edges) {
            if (edge == edgeId) {
                for (const auto& connectedEdge : tile.edges) {
                    if (connectedEdge != edgeId) {
                        connectedEdges.push_back(connectedEdge);
                    }
                }
            }
        }
    }
    return connectedEdges;
}


void Board::playRoadBuilding(int playerId) {
    std::cout << "Player " << playerId << " is playing Road Building. They can build two roads for free." << std::endl;
    for (int i = 0; i < 2; ++i) {
        int edgeId;
        std::cout << "Enter the edge ID for road " << (i + 1) << ": ";
        std::cin >> edgeId;
        if (canBuildRoad(edgeId, playerId)) {
            addRoad(edgeId, playerId);
            std::cout << "Player " << playerId << " built a road at edge " << edgeId << "." << std::endl;
        } 
        else {
            std::cout << "Cannot build road at edge " << edgeId << ". Try another edge." << std::endl;
            --i; // allow the player to try again if the road cannot be built
        }
    }
}

// year of plenty is a development card that allows the player to take any two resources of their choice
void Board::playYearOfPlenty(int playerId, ResourceType resourceType1, ResourceType resourceType2) {
    for (auto& player : players) {
        // find the player and give them the resources
        if (player.id == playerId) {
            player.gainResources(resourceType1, 1);
            player.gainResources(resourceType2, 1);
            std::cout << "Player " << playerId << " gains 1 " << resourceTypeToString(resourceType1) << " and 1 " << resourceTypeToString(resourceType2) << " from Year of Plenty." << std::endl;
            break;
        }
    }
}

void Board::playMonopoly(int playerId, ResourceType resourceType) {
    int totalResources = 0;
    // iterate over all players and take all of the specified resource from them
    for (auto& player : players) {
        if (player.id != playerId) {
            totalResources += player.resources[resourceType]; 
            player.resources[resourceType] = 0; // take all of the specified resource from the player
        }
    }
    // give all of the specified resource to the player
    for (auto& player : players) {
        if (player.id == playerId) {
            player.resources[resourceType] += totalResources;
            std::cout << "Player " << playerId << " gains all " << resourceTypeToString(resourceType) << " from other players, totaling " << totalResources << " resources." << std::endl;
            break;
        }
    }
}


