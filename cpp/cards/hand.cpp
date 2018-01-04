#include <ctime>
#include <cstdlib>



#include "hand.h"

//char suits[] = {'C', 'D', 'H', 'S'};

Hand::Hand()
{}

Hand::Hand(const Hand& _hand)
{
    m_hand = _hand.m_hand;
}

Hand& Hand::operator=(const Hand& _hand)
{
    if(&_hand != this)
    {
        m_hand = _hand.m_hand;
    }
    
    return *this;
}

Hand::~Hand()
{}

bool Hand::InsertInPlace(Card& _card)
{
    unsigned int i = 0;
    vector<Card>::iterator it = m_hand.begin();
    
    for(; i < m_hand.size() && _card.GetSuit() > m_hand[i].GetSuit(); ++i)
    {
        it++;
    }
    
    for(; i < m_hand.size() && _card.GetRank() > m_hand[i].GetRank() && _card.GetSuit() >= m_hand[i].GetSuit(); ++i)
    {
        it++;
    }
    m_hand.insert(it, _card);
}

Card Hand::Attack()
{
    srand(time(0));
    unsigned int index = rand() % m_hand.size();
    Card card = m_hand[index];
    
    vector<Card>::iterator it = m_hand.begin() + index;
    m_hand.erase(it);
    
    card.GetSuit();
    return card;
}

void Hand::ShowHand() const
{
    for(unsigned int i = 0; i < m_hand.size(); i += 1)
    {
        m_hand[i].PrintCard();
    }
    cout << endl;
}

bool Hand::Defend(Card& _card)
{
    unsigned int i = 0;
    vector<Card>::iterator it = m_hand.begin();

    //find higher card
    for(; i < m_hand.size() && _card.GetSuit() > m_hand[i].GetSuit(); ++i)
    {
        it++;
    }
    
    for(; i < m_hand.size() && _card.GetRank() > m_hand[i].GetRank() && _card.GetSuit() >= m_hand[i].GetSuit(); ++i)
    {
        it++;
    }

    if(_card.GetSuit() != m_hand[i].GetSuit())
    {
        InsertInPlace(_card);
        return false;
    }
    else
    {
        m_hand.erase(it);
        return true;
    }
}












