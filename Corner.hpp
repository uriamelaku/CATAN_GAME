#ifndef CORNER_HPP
#define CORNER_HPP

enum class BuildingType { NONE, SETTLEMENT, CITY };

class Corner {
public:
    BuildingType building;
    int owner; // who is the owner of the corner (e.g. player number)

    Corner();
};

#endif // CORNER_HPP
