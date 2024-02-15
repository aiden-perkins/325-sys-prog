// Aiden Perkins
// CECS 325-02
// Prog 1 – One Card War
// Due 2-15-2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include "Deck.h"

using namespace std;

Deck::Deck() {
    for (char suit: {'C', 'S', 'D', 'H'}) {
        for (char rank: {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'}) {
            cards.emplace_back(suit, rank);
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
    srand(time(nullptr));
    vector<Card> new_deck;
    for (int i = cards.size(); i > 0; i--) {
        int rand_value = rand() % i;
        new_deck.push_back(cards[rand_value]);
        cards.erase(cards.begin() + rand_value);
    }
    cards = new_deck;
}
