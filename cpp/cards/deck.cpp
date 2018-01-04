
//#include "card.h"
#include "deck.h"
#include <iostream>
#include <algorithm>

using namespace std;



//char suits[] = {'C', 'D', 'H', 'S'};
char ranks[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};


Deck::Deck()
{
    for (unsigned int j = 0; j < 13; j += 1)
    {
        Card cardc(C, ranks[j]);
        m_deck.push_back(cardc);
        Card cardd(D, ranks[j]);
        m_deck.push_back(cardd);
        Card cardh(H, ranks[j]);
        m_deck.push_back(cardh);
        Card cards(S, ranks[j]);
        m_deck.push_back(cards);
    }
}

Deck::~Deck()
{}

void Deck::Shuffle()
{
    srand(time(0));
    random_shuffle(m_deck.begin(), m_deck.end());
}

Card Deck::DrawCard()
{
    Card card = m_deck.back();
    m_deck.pop_back();
    return card;    
}

void Deck::PrintDeck() const
{
    for (unsigned int i = 0; i < 52; i += 1)
    {
        m_deck[i].PrintCard();
    }
}


