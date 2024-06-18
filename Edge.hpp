#ifndef EDGE_HPP
#define EDGE_HPP

enum class RoadType { NONE, ROAD };

class Edge {
public:
    RoadType road;
    int owner; // who is the owner of the road (e.g. player number)

    Edge();
};

#endif // EDGE_HPP
