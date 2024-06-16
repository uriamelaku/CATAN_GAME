#ifndef RESOURCE_TYPE_HPP
#define RESOURCE_TYPE_HPP

#include <string>

enum class ResourceType {
    FOREST, HILL, PASTURE, FIELD, MOUNTAIN, DESERT, WOOD, BRICK, SHEEP, WHEAT, ORE, NONE
};

std::string resourceTypeToString(ResourceType type);

#endif // RESOURCE_TYPE_HPP
