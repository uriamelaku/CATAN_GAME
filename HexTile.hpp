#ifndef HEX_TILE_HPP
#define HEX_TILE_HPP

#include <vector>
#include <string>
#include "ResourceType.hpp"

class HexTile {
private:
    int number; 

public:
    ResourceType type; // type of resource
    std::vector<int> corners; // indices of corners
    std::vector<int> edges; // indices of edges

    HexTile(ResourceType type = ResourceType::DESERT, int number = 0);

    std::string getTypeString() const;
    int getNumber() const;
    bool hasRobber;
};

#endif // HEX_TILE_HPP
