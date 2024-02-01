// Aiden Perkins
// CECS 325-02
// Prog 1 – Counting Letters
// Due 2-15-2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include "Deck.h"

using namespace std;

Deck::Deck() {
    for (char suit: {'C', 'S', 'D', 'H'}) {
        for (string rank: {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"}) {
            cards.push_back(Card(suit, rank));
        }
    }
}

Card Deck::deal() {
    Card card = cards.back();
    cards.pop_back();
    return card;
}

void Deck::display() {
    for (int i = 0; i < cards.size(); i++) {
        cards[i].display();
        if ((i + 1) % 13) {
            cout << ',';
        } else {
            cout << endl;
        }
    }
    cout << endl;
}

void Deck::shuffle() {

}
