#ifndef __HAND_H__
#define __HAND_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 
 
#include "card.h"
#include <vector>
using namespace std;

class Hand
{
public:
    Hand();
    Hand(const Hand& _hand);
    Hand& operator=(const Hand& _hand);
    virtual ~Hand();
    
    bool InsertInPlace(Card& _card);
    Card Attack();
    bool Defend(Card& _card);
    bool IsEmpty();
    unsigned int Counter();
    void ShowHand() const;
    
private:
    std::vector<Card> m_hand;
    
};

inline unsigned int Hand::Counter()
{
    return m_hand.size();
}

inline bool Hand::IsEmpty()
{
    return m_hand.size() == 0;
}
#endif /* __HAND_H__ */

