#include "ResourceType.hpp"

std::string resourceTypeToString(ResourceType type) {
    switch (type) {
        case ResourceType::FOREST: return "forest";
        case ResourceType::HILL: return "hill";
        case ResourceType::PASTURE: return "pasture";
        case ResourceType::FIELD: return "field";
        case ResourceType::MOUNTAIN: return "mountain";
        case ResourceType::DESERT: return "desert";
        case ResourceType::WOOD: return "wood"; // get from FOREST
        case ResourceType::WOOL: return "wool"; // get from FIELD
        case ResourceType::BRICK: return "brick"; // get from HILL
        case ResourceType::IRON: return "iron"; // get from MOUNTAIN
        case ResourceType::WHEAT: return "wheat"; // get from PASTURE
        case ResourceType::NONE: return "none";
        default: return "unknown";
    }
}
