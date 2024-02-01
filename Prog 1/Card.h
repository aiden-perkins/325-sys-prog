// Aiden Perkins
// CECS 325-02
// Prog 1 – Counting Letters
// Due 2-15-2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#ifndef CARD_H
#define CARD_H
#include <string>

using namespace std;

class Card {
    public:
        Card(char suit, string rank);  // constructor to create a card, setting the suit and rank
        void display();  // display the card example: AC, 10S, KD
        int compare(Card card);  // return 1 for win, 0 for tie, -1 for lose
        char suit;
        string rank;
};

#endif //CARD_H
