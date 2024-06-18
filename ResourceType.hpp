#ifndef RESOURCE_TYPE_HPP
#define RESOURCE_TYPE_HPP

#include <string>

enum class ResourceType {
    FOREST, HILL, PASTURE, FIELD, MOUNTAIN, IRON, DESERT, WOOD, BRICK, WHEAT, WOOL, NONE
};

std::string resourceTypeToString(ResourceType type);

#endif // RESOURCE_TYPE_HPP
