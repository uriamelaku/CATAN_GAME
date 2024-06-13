#include "Board.hpp"
#include <iostream>
#include <sstream>
#include <map>


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
/*
void Board::printGame() const {
    // מבנה האריחים בלוח קטאן:
    //          0    1    2
    //       3    4    5    6
    //    7    8    9   10   11
    //       12   13   14   15
    //          16   17   18

    const std::array<std::array<int, 5>, 5> layout = {{
        {-1,  0,  1,  2, -1},
        { 3,  4,  5,  6, -1},
        { 7,  8,  9, 10, 11},
        {-1, 12, 13, 14, 15},
        {-1, 16, 17, 18, -1}
    }};

    const std::string emptyHex = "                   ";

    auto getHexRepresentation = [&](int tileIndex) -> std::vector<std::string> {
        if (tileIndex == -1) {
            return {emptyHex, emptyHex, emptyHex, emptyHex, emptyHex, emptyHex, emptyHex, emptyHex, emptyHex};
        }

        const HexTile& tile = tiles[tileIndex];
        std::vector<std::string> hex = {
            "   1------2   ",
            "  /        \\  ",
            " /          \\ ",
            "3            4",
            " \\          / ",
            "  \\        /  ",
            "   6------5   "
        };

        std::string numStr = std::to_string(tile.getNumber());
        std::string typeStr = tile.getTypeString().substr(0, 5);

        hex[3].replace(6, numStr.length(), numStr); // Replace with number in the middle
        hex[4].replace(6 - typeStr.length() / 2, typeStr.length(), typeStr); // Replace with resource type below the number

        // Add corner numbers
        std::string corner0 = std::to_string(tile.corners[0]);
        std::string corner1 = std::to_string(tile.corners[1]);
        std::string corner2 = std::to_string(tile.corners[2]);
        std::string corner3 = std::to_string(tile.corners[3]);
        std::string corner4 = std::to_string(tile.corners[4]);
        std::string corner5 = std::to_string(tile.corners[5]);

        hex[0].replace(3, corner0.length(), corner0); // Top left corner
        hex[0].replace(10, corner1.length(), corner1); // Top right corner
        hex[3].replace(0, corner2.length(), corner2); // Mid left corner
        hex[3].replace(13, corner3.length(), corner3); // Mid right corner
        hex[6].replace(3, corner4.length(), corner4); // Bottom left corner
        hex[6].replace(10, corner5.length(), corner5); // Bottom right corner

        return hex;
    };

    std::vector<std::vector<std::string>> rows;
    for (const auto& row : layout) {
        std::vector<std::vector<std::string>> hexRow;
        for (int tileIndex : row) {
            hexRow.push_back(getHexRepresentation(tileIndex));
        }

        for (int i = 0; i < 7; ++i) {
            std::string rowStr;
            for (const auto& hex : hexRow) {
                rowStr += hex[i];
            }
            rows.push_back({rowStr});
        }
    }

    for (const auto& row : rows) {
        std::cout << row[0] << std::endl;
    }
}
*/

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
        if (resource.length() > 5) {
            resource = resource.substr(0, 5); // Limit resource type to 5 characters
        }
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













    bool Board::addSettlement(int cornerId, int playerId) {
        if (corners[cornerId].building != BuildingType::NONE) {
            std::cout << "Corner " << cornerId << " is already occupied." << std::endl;
            return false;
        }
        corners[cornerId].building = BuildingType::SETTLEMENT;
        corners[cornerId].owner = playerId;
        return true;
    }

    bool Board::addRoad(int edgeId, int playerId) {
    if (edges[edgeId].road != RoadType::NONE) {
        std::cout << "Edge " << edgeId << " is already occupied." << std::endl;
        return false;
    }
    edges[edgeId].road = RoadType::ROAD;
    edges[edgeId].owner = playerId;
    return true;
}

void Board::addPlayer(int playerId) {
    players.emplace_back(playerId);
}

int Board::rollDice() const {
    return (std::rand() % 6 + 1) + (std::rand() % 6 + 1);
}

bool Board::upgradeSettlement(int cornerId, int playerId) {
    // בדוק אם הפינה תפוסה
    if (corners[cornerId].building == BuildingType::NONE) {
        std::cout << "Corner " << cornerId << " is empty. Cannot upgrade to a city." << std::endl;
        return false;
    }
    
    // בדוק אם הפינה תפוסה על ידי יישוב של השחקן המבוקש
    if (corners[cornerId].building != BuildingType::SETTLEMENT || corners[cornerId].owner != playerId) {
        std::cout << "Corner " << cornerId << " cannot be upgraded by player " << playerId << "." << std::endl;
        return false;
    }

    // שדרג את היישוב לעיר
    corners[cornerId].building = BuildingType::CITY;
    std::cout << "Player " << playerId << " upgraded a settlement to a city at corner " << cornerId << "." << std::endl;
    return true;
}

void Board::printPlayerStatus(int playerId) const {
    for (const auto& player : players) {
        if (player.id == playerId) {
            std::cout << "Player " << player.id << " Status:" << std::endl;
            std::cout << "  Settlements: " << player.settlements << std::endl;
            std::cout << "  Cities: " << player.cities << std::endl;
            std::cout << "  Roads: " << player.roads << std::endl;
            std::cout << "  Development Cards: ";
            for (const auto& card : player.developmentCards) {
                std::cout << static_cast<int>(card.type) << " ";
            }
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





    void Board::processCommand(const std::string& command, int playerId) {
    std::istringstream iss(command);
    std::string action;
    int id;
    iss >> action >> id;

    if (action == "build_settlement") {
        if (addSettlement(id, playerId)) {
            std::cout << "Player " << playerId << " built a settlement at corner " << id << "." << std::endl;
        }
    } else if (action == "upgrade_settlement") {
        if (upgradeSettlement(id, playerId)) {
            std::cout << "Player " << playerId << " upgraded a settlement to a city at corner " << id << "." << std::endl;
        }
    } else if (action == "build_road") {
        if (addRoad(id, playerId)) {
            std::cout << "Player " << playerId << " built a road at edge " << id << "." << std::endl;
        }
    } else if (action == "roll_dice") {
        int result = rollDice();
        std::cout << "Player " << playerId << " rolled the dice: " << result << std::endl;
    } else {
        std::cout << "Unknown command." << std::endl;
    }
}

/*
    bool upgradeSettlement(int cornerId, int playerId) {
        if (corners[cornerId].building != BuildingType::SETTLEMENT || corners[cornerId].owner != playerId) {
            std::cout << "Corner " << cornerId << " cannot be upgraded." << std::endl;
            return false;
        }
        corners[cornerId].building = BuildingType::CITY;
        return true;
    }

    bool addRoad(int edgeId, int playerId) {
        if (edges[edgeId].road != RoadType::NONE) {
            std::cout << "Edge " << edgeId << " is already occupied." << std::endl;
            return false;
        }
        edges[edgeId].road = RoadType::ROAD;
        edges[edgeId].owner = playerId;
        return true;
    }

    void print() const {
        for (int i = 0; i < tiles.size(); ++i) {
            std::cout << "Tile " << i << ": " << tiles[i].getTypeString() << "(" << tiles[i].getNumber() << ")\n";
        }
    }

    void printStatus() const {
        std::cout << "Corners status:" << std::endl;
        for (const auto& corner : corners) {
            std::cout << "Corner " << corner.first << ": ";
            if (corner.second.building == BuildingType::NONE) {
                std::cout << "None";
            } else if (corner.second.building == BuildingType::SETTLEMENT) {
                std::cout << "Settlement";
            } else {
                std::cout << "City";
            }
            std::cout << " (Owner: " << corner.second.owner << ")" << std::endl;
        }

        std::cout << "Edges status:" << std::endl;
        for (const auto& edge : edges) {
            std::cout << "Edge " << edge.first << ": ";
            if (edge.second.road == RoadType::NONE) {
                std::cout << "None";
            } else {
                std::cout << "Road";
            }
            std::cout << " (Owner: " << edge.second.owner << ")" << std::endl;
        }
    }
    */
