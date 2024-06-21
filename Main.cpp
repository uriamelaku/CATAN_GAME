//ooriamelaku@gmail.com
//208734889
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
#include <array>
#include <string>


void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

using namespace std;

int main() {
    Board board;
    board.initialize();
    board.printBoard();
    cout << "Welcome to Catan!\n" << endl;
    cout << "First, let's add some players to the game." << endl;
    cout << "Each player will be assigned a number." << endl;
    cout << "The order of play will be the order in which players are added." << endl;
    cout << "The game will continue in a loop until a player enters the command 'exit'." << endl;
    cout << "The ROBBER will be placed on the desert tile at the start of the game.\n" << endl;
    cout << "Let's get started!\n" << endl;

    std::vector<int> playerIds;
    int numPlayers;

    std::cout << "Enter the number of players: ";
    std::cin >> numPlayers;
    std::cin.ignore(); // Ignore the newline character after the number

    for (int i = 1; i <= numPlayers; ++i) {
        playerIds.push_back(i);
        board.addPlayer(i);
    }

    // Add resources and cards to the players for testing purposes
    board.addAlotOfResourcesAndCards();

    std::string command;
    int currentPlayer = 0;
    bool diceRolled = false;

    while (true) {
        bool validMove = false;
        std::cout << "Commands:                      \nType the number of the command BUT in 6 write the full command\n";
        std::cout << "\n1. roll_dice            5. draw_card\n";
        std::cout << "2. build_road           6. trade_with_bank <NameOfGiveSource> <NameOfTakenSource> (ratio 4:1)\n";
        std::cout << "3. build_settlement     7. exit\n";
        std::cout << "4. upgrade_settlement   8. end my turn\n";
        std::cout << "                        9. play card\n";
        std::cout << std::endl;
        std::cout << "Player " << playerIds[currentPlayer] << ", enter your command: ";
        here:
        std::getline(std::cin, command);
        if(command == "") {
            goto here;
        }
        if (command == "7") {
            clearScreen();
            board.printAllPlayersStatus();
            break;
        }
        if (command == "8") {
            if (diceRolled) {
                clearScreen();
                currentPlayer = (currentPlayer + 1) % playerIds.size();
                diceRolled = false;
                std::cout << "Turn ended. Next player's turn.\n";
            } else {
                std::cout << "You must roll the dice before ending your turn.\n";
            }
            continue;
        }
        if (command.find("trade_with_bank") == 0) {
            board.processCommandWithBankTrade(command, playerIds[currentPlayer]);
            validMove = true; 
        } 
        else if(command == "9" || command == "6" || command == "5" || command == "4" || command == "3" || command == "2" || command == "1") {
            board.processCommand(command, playerIds[currentPlayer], validMove);
            validMove = true;
        }

        // Check if the roll_dice command was issued
        if (command == "1" && validMove) {
            diceRolled = true;
            validMove = true;
        }
        else if (!validMove) {
            std::cout << "Invalid command. Please try again.\n";
        }


    }

    return 0;
}
