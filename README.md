# Catan Game Explanation
Overview
This project is a command-line implementation of the popular board game "Catan". The game is played by multiple players who take turns to build settlements, roads, and cities, trade resources, and play development cards. The goal is to be the first player to reach 10 victory points.
Game Commands
Commands are used to interact with the game. Each command corresponds to an action a player can take. Here is a list of available commands:

#### Roll Dice
- Command: 1
- Description: Roll the dice to generate resources for the current turn. If the dice roll is 7, the robber is activated, which blocks resources from the tile it occupies and forces players with more than 7 resources to discard half.

#### Build Road
- Command: 2
- Description: Build a road on a specified edge if the player has the necessary resources.
- Example: 2 5 (build a road on edge 5)

#### Build Settlement
- Command: 3
- Description: Build a settlement on a specified corner if the player has the necessary resources.
- Example: 3 10 (build a settlement on corner 10)
#### Upgrade Settlement to City
- Command: 4
- Description: Upgrade an existing settlement to a city on a specified corner if the player has the necessary resources.
- Example: 4 15 (upgrade the settlement on corner 15 to a city)
#### Draw Development Card
- Command: 5
Description: Draw a development card if the player has the required resources (1 Ore, 1 Wheat, 1 Sheep).
#### Trade with Bank
- Command: 6 <giveResource> <getResource>
- Description: Trade 4 of one resource for 1 of another resource with the bank.
- Example: 6 WOOD BRICK (trade 4 WOOD for 1 BRICK)
#### Play Development Card
- Command: play_card
- Description: Play a development card by specifying the card type.
- Example: play_card road_building
- Valid Card Types: road_building, year_of_plenty, monopoly
#### End Turn
- Command: 8
- Description: End your turn and pass the turn to the next player.
#### Exit
- Command: 7
- Description: Exit the game.
### Development Cards
Development cards provide special abilities to players. Here are the types of development cards and their effects:

1. Road Building

Allows the player to build two roads for free.
2.Year of Plenty

Allows the player to take any two resources of their choice.
3.Monopoly

Allows the player to take all of one resource from all other players.
#### Robber
When a dice roll is 7:

1. No resources are distributed.
2. Players with more than 7 resources must 
3. discard half of their resources.
The current player moves the robber to a new tile, blocking resource generation for that tile.
### Victory Points
Victory points determine the winner of the game. The first player to reach 10 victory points wins. Points are earned as follows:

1. Settlements: 1 point each
2. Cities: 2 points each
3. Longest Road: 2 points (minimum 5 connected roads, only one player can have this at a time)
4. Largest Army: 2 points (first player to play 3 Knight cards, only one player can have this at a time)
5. Victory Point Cards: 1 point each
### Functions
Here is a brief explanation of some key functions in the game:

#### Board Class Functions
- initialize(): Sets up the initial board state, including tiles, corners, and edges.
- printBoard(): Prints the current state of the board.
- addPlayer(int playerId): Adds a player to the game.
- rollDice(): Rolls the dice to generate a number between 2 and 12.
distributeResources(int diceRoll): Distributes resources to players based on the dice roll.
moveRobber(int tileId): Moves the robber to the specified tile.
- handleRobber(): Handles the event when a 7 is rolled, forcing players to discard resources and move the robber.
- addSettlement(int cornerId, int playerId): Adds a settlement for a player if they have the resources and the corner is valid.
- upgradeSettlement(int cornerId, int playerId): Upgrades a settlement to a city if the player has the resources.
- addRoad(int edgeId, int playerId): Adds a road for a player if they have the resources and the edge is valid.
- drawDevelopmentCard(int playerId): Draws a development card for the player if they have the resources.
- processCommand(const std::string& command, int playerId, bool& validMove): Processes a game command entered by a player.
- processCommandWithBankTrade(const std::string& command, int playerId): Processes a trade command with the bank.
- playDevelopmentCard(int playerId, const std::string& cardType): Plays a specified development card.
- playRoadBuilding(int playerId): Plays the Road Building card.
- playYearOfPlenty(int playerId): Plays the Year of Plenty card.
- playMonopoly(int playerId): Plays the Monopoly card.
- calculateLongestRoad(int playerId): Calculates the longest road for a player.
- endGame() const: Ends the game and declares the winner.
### Player Class Functions
- Player(int id): Constructor to initialize a player with default resources and counts.
- addDevelopmentCard(const DevelopmentCard& card): Adds a development card to the player's hand.
- hasResources(const std::unordered_map<ResourceType, int>& cost) const: Checks if the player has the specified resources.
- spendResources(const std::unordered_map<ResourceType, int>& cost): Deducts the specified resources from the player.
- gainResources(ResourceType type, int amount): Adds resources to the player's inventory.
- tradeWithBank(ResourceType giveResource, ResourceType getResource): Trades resources with the bank at a 4:1 ratio.
- calculateVictoryPoints(): Calculates the total victory points for the player.
### Connections Between Functions
- The main game loop (main()) takes player input and calls processCommand() or processCommandWithBankTrade() to handle the input.
- processCommand() handles actions like rolling dice, building, upgrading, and drawing cards, updating the game state and player resources accordingly.
- distributeResources() is called when dice are rolled to give players resources based on their settlements and cities.
- Development card functions (playRoadBuilding(), playYearOfPlenty(), playMonopoly()) are called when players play specific development cards.
- calculateVictoryPoints() and calculateLongestRoad() are used to determine the winner and award points for the longest road.
The game is designed to ensure that each player can take actions, gain resources, and strategize to reach 10 victory points and win the game. The robber mechanism and development cards add complexity and strategic depth to the gameplay.
