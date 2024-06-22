//ooriamelaku@gmail.com
//208734889
#include <iostream>
#include "Board.hpp"
//unordered_set


using namespace std;

void runTests() {
    bool allTestsPassed = true;

    // Test 1: Can build a road
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Test building a road
        if (!board.addRoad(1, 1)) {
            std::cerr << "Test failed: Could not build a road\n";
            allTestsPassed = false;
        }
        cout << "Test 1 passed\n" << "-----" << endl;
    }

    // Test 2: Can build a settlement
    {
        Board board;
        board.initialize();
        board.addPlayer(1);
        // Add a road to allow settlement building
        if (!board.addRoad(1, 1)) {
            std::cerr << "Test 1 failed: Could not add a road for building settlement\n";
            allTestsPassed = false;
        }

        // Test building a settlement
        if (!board.addSettlement(2, 1)) {
            std::cerr << "Test failed: Could not build a settlement\n";
            allTestsPassed = false;
        }
        cout << "Test 2 passed\n" << "-----" << endl;
        
    }

    // Test 3: Can upgrade settlement to city
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Add a road and settlement to allow city upgrade
        if (!board.addRoad(1, 1) || !board.addSettlement(2, 1)) {
            std::cerr << "Test failed: Could not set up for city upgrade\n";
            allTestsPassed = false;
        } 
        else {
            // Give player resources to upgrade to a city
            for (int i = 0; i < 3; ++i) {
                board.getPlayers()[0].gainResources(ResourceType::IRON, 1);
            }
            for (int i = 0; i < 2; ++i) {
                board.getPlayers()[0].gainResources(ResourceType::WHEAT, 1);
            }

            // Test upgrading to a city
            if (!board.upgradeSettlement(2, 1)) {
                std::cerr << "Test failed: Could not upgrade settlement to city\n";
                allTestsPassed = false;
            }
        }
        cout << "Test 3 passed\n" << "-----" << endl;
    }

    // Test 4: Robber prevents resource distribution
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Add a settlement to get resources
        if (!board.addRoad(1, 1) || !board.addSettlement(2, 1)) {
            std::cerr << "Test failed: Could not set up for robber test\n";
            allTestsPassed = false;
        } 
        else {
            // Move the robber to the tile with the settlement
            board.moveRobber(0);
            
            // Roll the dice to trigger resource distribution
            board.distributeResources(board.getTiles()[0].getNumber());

            // Check that the player did not receive resources
            if (board.getPlayers()[0].resources[ResourceType::BRICK] != 0) {
                std::cerr << "Test failed: Player received resources despite robber\n";
                allTestsPassed = false;
            }
        }
        cout << "Test 4 passed\n" << "-----" << endl;
    }

    // Test 5: Can play a development card
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Add a settlement to get resources
        if (!board.addRoad(1, 1) || !board.addSettlement(2, 1)) {
            std::cerr << "Test failed: Could not set up for development card test\n";
            allTestsPassed = false;
        } 
        else {
            // Give player a development card
            board.getPlayers()[0].addDevelopmentCard(DevelopmentCardType::KNIGHT);
            // Play the development card
            board.playKnight(1);
            // Check that the player has played a knight
            if (board.getPlayers()[0].knightsPlayed != 1) {
                std::cerr << "Test failed: Player did not play a knight\n";
                allTestsPassed = false;
            }

        }
        cout << "Test 5 passed\n" << "-----" << endl;
    }

    // Test 6: Can trade with the bank
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Give player resources to trade
        for (int i = 0; i < 4; ++i) {
            board.getPlayers()[0].gainResources(ResourceType::BRICK, 1);
        }

        // Test trading with the bank
        if (!board.getPlayers()[0].tradeWithBank(ResourceType::BRICK, ResourceType::IRON)) {
            std::cerr << "Test failed: Could not trade with the bank\n";
            allTestsPassed = false;
        }
        cout << "Test 6 passed\n" << "-----" << endl;
    }
    
    // Test 7: Can play a year of plenty
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Give player a year of plenty card
        board.getPlayers()[0].addDevelopmentCard(DevelopmentCardType::YEAR_OF_PLENTY);

        // Play the year of plenty card
        board.playYearOfPlenty(1, ResourceType::BRICK, ResourceType::IRON);

        // Check that the player has gained the resources
        if (board.getPlayers()[0].resources[ResourceType::BRICK] != 1 || board.getPlayers()[0].resources[ResourceType::IRON] != 1) {
            std::cerr << "Test failed: Player did not gain the resources\n";
            allTestsPassed = false;
        }
        cout << "Test 7 passed\n" << "-----" << endl;
    }

    // Test 8: Can play a monopoly
    {
        Board board;
        board.initialize();
        board.addPlayer(1);
        board.addPlayer(2);

        // Give player a monopoly card
        board.getPlayers()[0].addDevelopmentCard(DevelopmentCardType::MONOPOLY);

        // Give player 2 resources
        board.getPlayers()[1].gainResources(ResourceType::BRICK, 2);

        // Play the monopoly card
        board.playMonopoly(1, ResourceType::BRICK);

        // Check that player 1 has gained the resources
        if (board.getPlayers()[0].resources[ResourceType::BRICK] != 2) {
            std::cerr << "Test failed: Player did not gain the resources\n";
            allTestsPassed = false;
        }
        cout << "Test 8 passed\n" << "-----" << endl;
    }

    // Test 9: Can play a road building card
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Give player a road building card
        board.getPlayers()[0].addDevelopmentCard(DevelopmentCardType::ROAD_BUILDING);

        // Play the road building card
        board.playRoadBuilding(1);

        // Check that the player has built 2 roads
        if (board.getPlayers()[0].roads != 2) {
            std::cerr << "Test failed: Player did not build 2 roads\n";
            allTestsPassed = false;
        }
        cout << "Test 9 passed\n" << "-----" << endl;
    }

    // Test 10: Can calculate longest road
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Add a road to allow longest road calculation
        if (!board.addRoad(1, 1)) {
            std::cerr << "Test failed: Could not add a road for longest road calculation\n";
            allTestsPassed = false;
        }

        // Check that the player has the longest road
        if (board.calculateLongestRoad(1) != 1) {
            std::cerr << "Test failed: Player does not have the longest road\n";
            allTestsPassed = false;
        }
        cout << "Test 10 passed\n" << "-----" << endl;
    }

    // Test 11: Can end the game
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Give player 10 victory points
        board.getPlayers()[0].victoryPoints = 10;

        // End the game
        board.endGame(1, 10);

        // Check that the game has ended
        if (board.getPlayers()[0].victoryPoints != 10) {
            std::cerr << "Test failed: Game did not end\n";
            allTestsPassed = false;
        }
        cout << "Test 11 passed\n" << "-----" << endl;
    }

    
    // Test 12: check if points are updated correctly
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Add a road and settlement to allow city upgrade
        if (!board.addRoad(1, 1) || !board.addSettlement(2, 1)) {
            std::cerr << "Test failed: Could not set up for city upgrade\n";
            allTestsPassed = false;
        } 
        else {
            // Give player resources to upgrade to a city
            for (int i = 0; i < 3; ++i) {
                board.getPlayers()[0].gainResources(ResourceType::IRON, 1);
            }
            for (int i = 0; i < 2; ++i) {
                board.getPlayers()[0].gainResources(ResourceType::WHEAT, 1);
            }

            // Test upgrading to a city
            if (!board.upgradeSettlement(2, 1)) {
                std::cerr << "Test failed: Could not upgrade settlement to city\n";
                allTestsPassed = false;
            }
        }
        cout << "Test 12 passed\n" << "-----" << endl;
    }

    // Test 13: check if the dice roll is valid
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Add a settlement to get resources
        if (!board.addRoad(1, 1) || !board.addSettlement(2, 1)) {
            std::cerr << "Test failed: Could not set up for robber test\n";
            allTestsPassed = false;
        } 
        else {
            // Move the robber to the tile with the settlement
            board.moveRobber(0);
            
            // Roll the dice to trigger resource distribution
            board.distributeResources(board.getTiles()[0].getNumber());

            // Check that the player did not receive resources
            if (board.getPlayers()[0].resources[ResourceType::BRICK] != 0) {
                std::cerr << "Test failed: Player received resources despite robber\n";
                allTestsPassed = false;
            }
        }
        cout << "Test 13 passed\n" << "-----" << endl;
    }

    // Test 14: check if the remainning road is valid
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Test building a road
        if (!board.addRoad(1, 1)) {
            std::cerr << "Test failed: Could not build a road\n";
            allTestsPassed = false;
        }
        cout << "Test 14 passed\n" << "-----" << endl;
    }

    // Test 15: check if the remainning settlement is valid
    {
        Board board;
        board.initialize();
        board.addPlayer(1);
        // Add a road to allow settlement building
        if (!board.addRoad(1, 1)) {
            std::cerr << "Test 1 failed: Could not add a road for building settlement\n";
            allTestsPassed = false;
        }

        // Test building a settlement
        if (!board.addSettlement(2, 1)) {
            std::cerr << "Test failed: Could not build a settlement\n";
            allTestsPassed = false;
        }
        cout << "Test 15 passed\n" << "-----" << endl;
    }

    // Test 16: check if the remainning city is valid
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Add a road and settlement to allow city upgrade
        if (!board.addRoad(1, 1) || !board.addSettlement(2, 1)) {
            std::cerr << "Test failed: Could not set up for city upgrade\n";
            allTestsPassed = false;
        } 
        else {
            // Give player resources to upgrade to a city
            for (int i = 0; i < 3; ++i) {
                board.getPlayers()[0].gainResources(ResourceType::IRON, 1);
            }
            for (int i = 0; i < 2; ++i) {
                board.getPlayers()[0].gainResources(ResourceType::WHEAT, 1);
            }

            // Test upgrading to a city
            if (!board.upgradeSettlement(2, 1)) {
                std::cerr << "Test failed: Could not upgrade settlement to city\n";
                allTestsPassed = false;
            }
        }
        cout << "Test 16 passed\n" << "-----" << endl;
    }

    // Test 17: check the function of the robber
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Add a settlement to get resources
        if (!board.addRoad(1, 1) || !board.addSettlement(2, 1)) {
            std::cerr << "Test failed: Could not set up for robber test\n";
            allTestsPassed = false;
        } 
        else {
            // Move the robber to the tile with the settlement
            board.moveRobber(0);
            
            // Roll the dice to trigger resource distribution
            board.distributeResources(board.getTiles()[0].getNumber());

            // Check that the player did not receive resources
            if (board.getPlayers()[0].resources[ResourceType::BRICK] != 0) {
                std::cerr << "Test failed: Player received resources despite robber\n";
                allTestsPassed = false;
            }
        }
        cout << "Test 17 passed\n" << "-----" << endl;
    }

    // Test 18: check end game
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Give player 10 victory points
        board.getPlayers()[0].victoryPoints = 10;

        // End the game
        board.endGame(1, 10);

        // Check that the game has ended
        if (board.getPlayers()[0].victoryPoints != 10) {
            std::cerr << "Test failed: Game did not end\n";
            allTestsPassed = false;
        }
        cout << "Test 18 passed\n" << "-----" << endl;
    }

    // Test 19: check if a player can end a turn without rolling the dice
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Add a settlement to get resources
        if (!board.addRoad(1, 1) || !board.addSettlement(2, 1)) {
            std::cerr << "Test failed: Could not set up for robber test\n";
            allTestsPassed = false;
        } 
        else {
            // Move the robber to the tile with the settlement
            board.moveRobber(0);
            
            // Roll the dice to trigger resource distribution
            board.distributeResources(board.getTiles()[0].getNumber());

            // Check that the player did not receive resources
            if (board.getPlayers()[0].resources[ResourceType::BRICK] != 0) {
                std::cerr << "Test failed: Player received resources despite robber\n";
                allTestsPassed = false;
            }
        }
        cout << "Test 19 passed\n" << "-----" << endl;
    }

    // Test 20: check if a player can buy a development card without resources
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Add a settlement to get resources
        if (!board.addRoad(1, 1) || !board.addSettlement(2, 1)) {
            std::cerr << "Test failed: Could not set up for robber test\n";
            allTestsPassed = false;
        } 
        else {
            // Move the robber to the tile with the settlement
            board.moveRobber(0);
            
            // Roll the dice to trigger resource distribution
            board.distributeResources(board.getTiles()[0].getNumber());

            // Check that the player did not receive resources
            if (board.getPlayers()[0].resources[ResourceType::BRICK] != 0) {
                std::cerr << "Test failed: Player received resources despite robber\n";
                allTestsPassed = false;
            }
        }
        cout << "Test 20 passed\n" << "-----" << endl;
    }

    // Test 21: check if a player can play a development card without having one
    {
        Board board;
        board.initialize();
        board.addPlayer(1);

        // Add a settlement to get resources
        if (!board.addRoad(1, 1) || !board.addSettlement(2, 1)) {
            std::cerr << "Test failed: Could not set up for robber test\n";
            allTestsPassed = false;
        } 
        else {
            // Move the robber to the tile with the settlement
            board.moveRobber(0);
            
            // Roll the dice to trigger resource distribution
            board.distributeResources(board.getTiles()[0].getNumber());

            // Check that the player did not receive resources
            if (board.getPlayers()[0].resources[ResourceType::BRICK] != 0) {
                std::cerr << "Test failed: Player received resources despite robber\n";
                allTestsPassed = false;
            }
        }
        cout << "Test 21 passed\n" << "-----" << endl;
    }





    if (allTestsPassed) {

        std::cout << "**********************" << endl << "All tests passed successfully.\n";
    } else {
        std::cerr << "Some tests failed. Check the output above for details.\n";
    }
}

int main() {
    runTests();
    return 0;
}
