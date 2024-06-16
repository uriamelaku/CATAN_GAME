#ifndef HEX_TILE_HPP
#define HEX_TILE_HPP

#include <vector>
#include <string>
#include "ResourceType.hpp"

class HexTile {
private:
    int number; // קודם מספר

public:
    ResourceType type; // ואז סוג המשאב
    std::vector<int> corners; // indices of corners
    std::vector<int> edges; // indices of edges

    HexTile(ResourceType type = ResourceType::DESERT, int number = 0);

    std::string getTypeString() const;
    int getNumber() const;
};

#endif // HEX_TILE_HPP
