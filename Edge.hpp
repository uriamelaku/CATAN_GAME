#ifndef EDGE_HPP
#define EDGE_HPP

enum class RoadType { NONE, ROAD };

class Edge {
public:
    RoadType road;
    int owner; // מי הבעלים של הדרך (למשל, מספר השחקן)

    Edge();
};

#endif // EDGE_HPP
