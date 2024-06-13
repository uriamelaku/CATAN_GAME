#ifndef CORNER_HPP
#define CORNER_HPP

enum class BuildingType { NONE, SETTLEMENT, CITY };

class Corner {
public:
    BuildingType building;
    int owner; // מי הבעלים של הבניין (למשל, מספר השחקן)

    Corner();
};

#endif // CORNER_HPP
