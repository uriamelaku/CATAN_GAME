#include "ResourceType.hpp"

std::string resourceTypeToString(ResourceType type) {
    switch (type) {
        case ResourceType::FOREST: return "forest";
        case ResourceType::HILL: return "hill";
        case ResourceType::PASTURE: return "pasture";
        case ResourceType::FIELD: return "field";
        case ResourceType::MOUNTAIN: return "mountain";
        case ResourceType::DESERT: return "desert";
        case ResourceType::WOOD: return "wood";
        case ResourceType::BRICK: return "brick";
        case ResourceType::SHEEP: return "sheep";
        case ResourceType::WHEAT: return "wheat";
        case ResourceType::ORE: return "ore";
        case ResourceType::NONE: return "none";
        default: return "unknown";
    }
}
