#include "HexTile.hpp"

HexTile::HexTile(ResourceType type, int number) : type(type), number(number) {
    corners.resize(6, -1); // Initialize corners with -1 to indicate no connection
    edges.resize(6, -1); // Initialize edges with -1 to indicate no connection
}

std::string HexTile::getTypeString() const {
    switch (type) {
        case ResourceType::FOREST: return "forest"; //
        case ResourceType::HILL: return "hill"; //
        case ResourceType::PASTURE: return "pasture";
        case ResourceType::FIELD: return "field"; //
        case ResourceType::MOUNTAIN: return "mountain"; //
        case ResourceType::DESERT: return "desert"; //
        default: return "UN";
    }
}

int HexTile::getNumber() const {
    return number;
}
