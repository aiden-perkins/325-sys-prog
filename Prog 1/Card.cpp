// Aiden Perkins
// CECS 325-02
// Prog 1 – Counting Letters
// Due 2-15-2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include "Card.h"

using namespace std;

Card::Card(char suit, string rank) {
    Card::suit = suit;
    Card::rank = rank;
}

void Card::display() {
    cout << rank << suit;
}

int Card::compare(Card card) {
    return 0;
}
