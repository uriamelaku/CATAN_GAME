CXX = g++
CXXFLAGS = -Wall -std=c++17

SRCS = Main.cpp Board.cpp HexTile.cpp Corner.cpp Edge.cpp Player.cpp DevelopmentCard.cpp DevelopmentCardDeck.cpp ResourceType.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = Main

all: $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)
