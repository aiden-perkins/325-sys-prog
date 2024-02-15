// Aiden Perkins
// CECS 325-02
// Prog 1 – One Card War
// Due 2-15-2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <map>
#include "Card.h"

using namespace std;

Card::Card(char suit, char rank) {
    Card::suit = suit;
    Card::rank = rank;
}

void Card::display() const {
    if (rank == 'T') {
        cout << "10" << suit;
    } else {
        cout << rank << suit;
    }
}

int Card::compare(Card card) const {
    map<char, int> rank_map = {
        {'A', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5},
        {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
        {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}
    };
    if (rank == card.rank) {
        return 0;
    } else if (rank_map[rank] > rank_map[card.rank]) {
        return 1;
    } else {
        return -1;
    }
}
