//ooriamelaku@gmail.com
//208734889
#ifndef DEVELOPMENTCARDDECK_HPP
#define DEVELOPMENTCARDDECK_HPP

#include <vector>
#include "DevelopmentCard.hpp"

class DevelopmentCardDeck {
private:
    std::vector<DevelopmentCard> deck;
    void shuffleDeck();

public:
    DevelopmentCardDeck();
    DevelopmentCard drawCard();
};

#endif // DEVELOPMENTCARDDECK_HPP
