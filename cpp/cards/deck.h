#ifndef __DECK_H__
#define __DECK_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include "card.h"
#include <vector>

class Deck
{
public:
    Deck();
    virtual ~Deck();
    
    void Shuffle();
    bool Sort();
    
    Card DrawCard();
//    bool DrawBigger(Card& _card);     // == defend
//    Card& DrawRandom();               // == attack
    void PrintDeck() const;
    
private:
    /* data */
    std::vector<Card> m_deck;
    
private:
    Deck(const Deck& _Deck);
    Deck& operator=(const Deck& _Deck);
};

#endif /* __DECK_H__ */

