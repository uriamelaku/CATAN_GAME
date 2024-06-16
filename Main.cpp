#include <iostream>
#include "Board.hpp"
#include "Corner.hpp"
#include "Edge.hpp"
#include "HexTile.hpp"
#include "Player.hpp"
#include "DevelopmentCard.hpp"
#include "DevelopmentCardDeck.hpp"
#include <vector>
#include <unordered_map>
#include <array>
#include <string>

int main() {
    Board board;
    board.initialize();
    board.printBoard();

    std::vector<int> playerIds;
    int numPlayers;

    std::cout << "Enter the number of players: ";
    std::cin >> numPlayers;
    std::cin.ignore(); // Ignore the newline character after the number

    for (int i = 1; i <= numPlayers; ++i) {
        playerIds.push_back(i);
        board.addPlayer(i);
    }

    std::string command;
    int currentPlayer = 0;

    while (true) {
        bool validMove = false;
        std::cout << "Choose a command: roll_dice, build_road, build_settlement, upgrade_settlement, draw_card, exit\n" << std::endl;
        std::cout << "Player " << playerIds[currentPlayer] << ", enter your command (e.g., build_settlement 0): ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        }

        board.processCommand(command, playerIds[currentPlayer], validMove);

        // Check if the last move was valid before switching players
        if (validMove) {
            currentPlayer = (currentPlayer + 1) % playerIds.size();
        } 
        else {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }

    return 0;
}
