#ifndef __CARD_H__
#define __CARD_H__

/** 
 * @brief minimal class that creates card and give very minimal use of it.
 * @warning values are not checked!
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

#include <iostream>

typedef enum 
{
    C,
    D,
    H,
    S
}Suit;

class Card
{
public:
    // CTOR & DTOR
    Card(Suit _suit, char _rank);
    Card(const Card& _card);
    Card& operator=(const Card& _card);
    virtual ~Card();
    
    // minimal functionality
    Suit GetSuit()const;
    char GetRank()const;
    
    void PrintCard() const;
    unsigned int FindIndex(const char _rank)const;
        
    // operator
    bool operator>(const Card& _card) const;
    bool operator<=(const Card& _card) const;
    
private:
    /* data */
    Suit m_suit;
    char m_rank;

};


#endif /* __CARD_H__ */

