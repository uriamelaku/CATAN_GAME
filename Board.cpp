#include "Board.hpp"
#include <iostream>
#include <sstream>
#include <map>
#include <array>
#include <cstdlib>
#include <algorithm>



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
        // אתחול הפינות והקווים עבור כל אריח
        static const std::array<std::array<int, 6>, 19> cornerConnections = {{
            {0, 1, 2, 3, 4, 5},      // אריח 0*
            {6, 7, 8, 9, 2, 1},      // אריח 1
            {10, 11, 12, 13, 8, 7},  // אריח 2
            {4, 3, 14, 15, 16, 17},   // אריח 3
            {2, 9, 18, 19, 14, 3},  // אריח 4
            {8, 13, 20, 21, 18, 9}, // אריח 5
            {12, 22, 23, 24, 20, 13}, // אריח 6
            {16, 15, 25, 26, 27, 28},  // אריח 7
            {14, 19, 29, 30, 25, 15}, // אריח 8
            {18, 21, 31, 32, 29, 19}, // אריח 9
            {20, 24, 33, 34, 31, 21}, // אריח 10
            {23, 35, 36, 37, 33, 24}, // אריח 11
            {25, 30, 40, 39, 38, 26}, // אריח 12
            {29, 32, 42, 41, 40, 30}, // אריח 13
            {31, 34, 44, 43, 42, 32}, // אריח 14
            {33, 37, 46, 45, 44, 34}, // אריח 15
            {40, 41, 49, 48, 47, 39}, // אריח 16
            {42, 43, 51, 50, 49, 41}, // אריח 17
            {44, 45, 53, 52, 51, 43}, // אריח 18
        }};

        static const std::array<std::array<int, 6>, 19> edgeConnections = {{
            {1, 2, 3, 4, 5, 6},      // אריח 0
            {7, 8, 9, 10, 2, 11},     // אריח 1
            {12, 13, 14, 15, 8, 16}, // אריח 2
            {4, 17, 18, 19, 20, 21},   // אריח 3
            {10, 22, 23, 24, 17, 3},  // אריח 4
            {15, 25, 26, 27, 22, 9},// אריח 5
            {28, 29, 30, 31, 25, 14},// אריח 6
            {19, 32, 33, 34, 35, 36}, // אריח 7
            {24, 37, 38, 39, 32, 18},// אריח 8
            {27, 40, 41, 42, 37, 23},// אריח 9
            {31, 43, 44, 45, 40, 26},// אריח 10
            {46, 47, 48, 49, 43, 30},// אריח 11
            {39, 50, 51, 52, 53, 33},// אריח 12
            {42, 54, 55, 56, 50, 38},// אריח 13
            {45, 57, 58, 59, 54, 41},// אריח 14
            {49, 60, 61, 62, 57, 44},// אריח 15
            {56, 63, 64, 65, 66, 51},// אריח 16
            {59, 67, 68, 69, 63, 55},// אריח 17
            {62, 70, 71, 72, 67, 58},// אריח 18
        }};

        // חיבור הפינות והקווים לאריחים
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
        // if (resource.length() > 5) {
        //     resource = resource.substr(0, 5); // Limit resource type to 5 characters
        // }
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



bool Board::canBuildSettlement(int cornerId, int playerId) const {
    if (corners.at(cornerId).building != BuildingType::NONE) {
        return false; // כבר יש בנייה בפינה זו
    }

    // בדוק אם יש יישוב סמוך (במרחק של 2 פינות)
    for (const auto& tile : tiles) {
        if (std::find(tile.corners.begin(), tile.corners.end(), cornerId) != tile.corners.end()) {
            for (const auto& adjacentCorner : tile.corners) {
                if (cornerId != adjacentCorner && corners.at(adjacentCorner).building != BuildingType::NONE) {
                    return false; // יש יישוב סמוך
                }
            }
        }
    }

    // בדוק אם יש דרך סמוכה של השחקן שמחוברת לפינה
    for (const auto& tile : tiles) {
        if (std::find(tile.corners.begin(), tile.corners.end(), cornerId) != tile.corners.end()) {
            for (const auto& edge : tile.edges) {
                const auto& edgeTile = edges.at(edge);
                if (edgeTile.owner == playerId && edgeTile.road == RoadType::ROAD) {
                    return true; // יש דרך סמוכה של השחקן שמחוברת לפינה
                }
            }
        }
    }

    return false;
}


bool Board::canBuildRoad(int edgeId, int playerId) const {
    // בדיקה אם כבר יש דרך על הקצה המבוקש
    if (edges.at(edgeId).road != RoadType::NONE) {
        return false;
    }
    
    // בדיקה אם הקצה מחובר לפינה של השחקן המבוקש עם יישוב או עיר
    // for (const auto& tile : tiles) {
    //     for (int i = 0; i < 6; ++i) {
    //         if (tile.edges[i] == edgeId) {
    //             int corner1 = tile.corners[i];
    //             int corner2 = tile.corners[(i + 1) % 6];
    //             if ((corners.at(corner1).owner == playerId && (corners.at(corner1).building == BuildingType::SETTLEMENT || corners.at(corner1).building == BuildingType::CITY)) ||
    //                 (corners.at(corner2).owner == playerId && (corners.at(corner2).building == BuildingType::SETTLEMENT || corners.at(corner2).building == BuildingType::CITY))) {
    //                 return true;
    //             }
    //         }
    //     }
    // }

    return true;
}




void Board::addPlayer(int playerId) {
    players.emplace_back(playerId);
}

int Board::rollDice() const {
    return (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
}

bool Board::addRoad(int edgeId, int playerId) {
    for (auto& player : players) {
        if (player.id == playerId) {
            if (player.roadCount > 0) {
                if (canBuildRoad(edgeId, playerId)) {
                    edges[edgeId].road = RoadType::ROAD;
                    edges[edgeId].owner = playerId;
                    player.roads++;
                    player.roadCount--;
                    return true;
                } 
                else {
                    std::cout << "Cannot build road at edge " << edgeId << "." << std::endl;
                    return false;
                }
            } else {
                std::cout << "Player " << playerId << " has no more roads to place." << std::endl;
                return false;
            }
        }
    }
    std::cout << "Player " << playerId << " not found." << std::endl;
    return false;
}

bool Board::addSettlement(int cornerId, int playerId) {
    for (auto& player : players) {
        if (player.id == playerId) {
            if (player.settlementCount > 0) {
                if (canBuildSettlement(cornerId, playerId)) {
                    corners[cornerId].building = BuildingType::SETTLEMENT;
                    corners[cornerId].owner = playerId;
                    player.settlements++;
                    player.settlementCount--;
                    return true;
                } else {
                    std::cout << "Cannot build settlement at corner " << cornerId << "." << std::endl;
                    return false;
                }
            } else {
                std::cout << "Player " << playerId << " has no more settlements to place." << std::endl;
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
    for (const auto& tile : tiles) {
        if (tile.getNumber() == diceRoll) {
            for (const auto& cornerId : tile.corners) {
                const auto& corner = corners.at(cornerId);
                if (corner.building != BuildingType::NONE) {
                    for (auto& player : players) {
                        if (player.id == corner.owner) {
                            player.gainResources(tile.type, (corner.building == BuildingType::CITY) ? 2 : 1);
                        }
                    }
                }
            }
        }
    }
}



bool Board::upgradeSettlement(int cornerId, int playerId) {
    for (auto& player : players) {
        if (player.id == playerId) {
            if (player.cityCount > 0) {
                if (canUpgradeSettlement(cornerId, playerId)) {
                    corners[cornerId].building = BuildingType::CITY;
                    player.cities++;
                    player.settlements--;
                    player.cityCount--;
                    return true;
                } else {
                    std::cout << "Cannot upgrade settlement at corner " << cornerId << "." << std::endl;
                    return false;
                }
            } else {
                std::cout << "Player " << playerId << " has no more cities to place." << std::endl;
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
            std::cout << "  Development Cards: ";
            int count = 0;
            for (const auto& card : player.developmentCards) { 
               count++;
            }
            std::cout << "  Resources: ";
            for (const auto& resource : player.resources) {
                std::cout << resourceTypeToString(resource.first) << ": " << resource.second << " ";
            }
            std::cout << count;
            std::cout << std::endl;
            break;
        }
    }
}

void Board::printAllPlayersStatus() const {
    for (const auto& player : players) {
        printPlayerStatus(player.id);
        std::cout << std::endl; // שורה ריקה בין הסטטוסים של השחקנים
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

void Board::processCommand(const std::string& command, int playerId, bool& validMove) {
    std::istringstream iss(command);
    std::string action;
    int id;

    iss >> action;

    validMove = false;

    // roll_dice command
    if (action == "roll_dice") {
        int result = rollDice();
        std::cout << "Player " << playerId << " rolled the dice: " << result << std::endl;
        distributeResources(result);
        // to fix
        validMove =true;
    } 
    // build_settlement, upgrade_settlement, build_road - commands
    else if (action == "build_settlement" || action == "upgrade_settlement" || action == "build_road") {

        // if action is build_road, ask for edge ID
        std::cout << "Enter the " << (action == "build_road" ? "edge" : "corner") << " ID: ";
        std::cin >> id;
        std::cin.ignore(); // Ignore the newline character after the number
        
         
        if (action == "build_settlement") {
            if (addSettlement(id, playerId)) {
                std::cout << "Player " << playerId << " built a settlement at corner " << id << "." << std::endl;
                validMove = true;
            } 
            else {
                std::cout << "Failed to build settlement at corner " << id << "." << std::endl;
            }
        } 
        else if (action == "upgrade_settlement") {
            if (upgradeSettlement(id, playerId)) {
                std::cout << "Player " << playerId << " upgraded a settlement to a city at corner " << id << "." << std::endl;
                validMove = true;
            } else {
                std::cout << "Failed to upgrade settlement at corner " << id << "." << std::endl;
            }
        } 
        else if (action == "build_road") {
            if (addRoad(id, playerId)) {
                std::cout << "Player " << playerId << " built a road at edge " << id << "." << std::endl;
                validMove = true;
            } else {
                std::cout << "Failed to build road at edge " << id << "." << std::endl;
            }
        }
    } 
    // draw_card command
    else if (action == "draw_card") {
        DevelopmentCard card = drawDevelopmentCard(playerId);
        std::cout << "Player " << playerId << " drew a development card: " << card.getTypeString() << std::endl;
        validMove = true;
    } 
    else {
        std::cout << "Unknown command." << std::endl;
    }

    // if the move was valid, print the updated board and player status
    if (validMove) {
        // Update player status and board only if the move was valid
        printBoard();
        printAllPlayersStatus();
    }
}
