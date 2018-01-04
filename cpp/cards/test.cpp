#include "hand.h"
#include "deck.h"

int main()
{
    Deck deck;
    deck.Shuffle();
//    deck.PrintDeck();
    Hand hand[4];
    for(unsigned int i = 0; i < 13; ++i)
    {
        for(unsigned int j = 0; j < 4; ++j)
        {
            Card card(deck.DrawCard());
            hand[j].InsertInPlace(card);
        }
    }
    
    for(unsigned int i = 0; i < 4; ++i)
    {
        hand[i].ShowHand();
    }
    
 //   Card card();
    
    unsigned int numOfRounds = 0;
    cout << "Please enter num of desired rounds.\n";
    cin >> numOfRounds;
    cout << "Do you want prints after every round? (0 = no, 1 = yes)\n";
    bool prints;
    cin >> prints;
    
    bool win = true;
    for(unsigned int i = 0; i < numOfRounds * 4 ; ++i)
    {
        if(prints && i % 4 == 0)
        {
            cout << "round #" << i/4 << endl; 
            for(unsigned int j = 0; j < 4; ++j)
            {
                hand[j].ShowHand();
            }
        }
        
        Card card = hand[i % 4].Attack();
        win = hand[(i + 1) % 4].Defend(card);

        if(hand[i % 4].IsEmpty() || hand[(i + 1) % 4].IsEmpty())
        {
            if(hand[i % 4].IsEmpty())
            {
                cout << "Player #" << i % 4 << " won!!\n";
            }
            if(hand[(i + 1) % 4].IsEmpty())
            {
                cout << "Player #" << (i + 1) % 4 << " won!!\n";
            }
            for(unsigned int j = 0; j < 4; ++j)
            {
                hand[j].ShowHand();
            }
            cout << "i = " << i % 4 << endl;
            return 0;
        }
        
        if(win == false)
        {
            ++i;
        }
    }
    
    unsigned int winner = min(min(hand[0].Counter(), hand[1].Counter()), min(hand[2].Counter(), hand[3].Counter()));
    cout << "Player(s) ";
    for(unsigned int i = 0; i < 4; ++i)
    {
        if(hand[i].Counter() == winner)
        {
            cout << i << " ";
        }
    }
    cout << "won, with " << winner << " cards\n";
    
    for(unsigned int j = 0; j < 4; ++j)
    {
        hand[j].ShowHand();
    }
    
    return 0;
}
