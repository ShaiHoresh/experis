
#include "card.h"
using namespace std;

char mrank[] = {'2','3','4','5','6','7','8','9','T','J','Q','K','A'};

unsigned int Card::FindIndex(const char _rank)const
{
    for (unsigned int i = 0; i < 13; i += 1)
    {
        if(_rank == mrank[i])
        {
            return i;
        }
    }
    return 0;
}

Card::Card(Suit _suit, char _rank)
{
    m_suit = _suit;
    m_rank = _rank;
}

Card::Card(const Card& _card)
{
    m_suit = _card.m_suit;
    m_rank = _card.m_rank;
}

Card& Card::operator=(const Card& _card)
{
    m_suit = _card.m_suit;
    m_rank = _card.m_rank;
    
    return *this;
}

Card::~Card()
{}

Suit Card::GetSuit() const
{
    return m_suit;
}

char Card::GetRank() const
{
    return m_rank;
}

bool Card::operator>(const Card& _card) const
{
    unsigned int me = FindIndex(m_rank);
    unsigned int him = FindIndex(_card.m_rank);
    
    return (m_suit == _card.m_suit && me > him);
}

bool Card::operator<=(const Card& _card) const
{
    return (_card > *this);
}

void Card::PrintCard() const
{
    cout << m_suit << m_rank << "  ";
}
/*
int main()
{
    Card me('D', 'K');
    Card him('D', '9');
    
    me.PrintCard();
    him.PrintCard();
    
    cout << (me > him) << endl;
    cout << (me <= him) << endl;
    
    return 0;
}
*/
