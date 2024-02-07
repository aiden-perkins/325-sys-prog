// Aiden Perkins
// CECS 325-02
// Prog 1 – One Card War
// Due 2-15-2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <string>
#include <iomanip>
#include "Deck.h"

using namespace std;

int main() {
    // A new deck will be created.
    Deck deck;
    // The program will ask for the names of the 2 players.
    string player1Name;
    int player1Wins = 0;
    int player1Losses = 0;
    string player2Name;
    int player2Wins = 0;
    int player2Losses = 0;
    int ties = 0;
    cout << "Enter the name of the first player: ";
    cin >> player1Name;
    cout << "Enter the name of the second player: ";
    cin >> player2Name;
    cout << endl;
    // The unshuffled deck will be displayed on the screen.
    cout << " Original Deck" << endl;
    deck.display();
    // The deck will be shuffled.
    deck.shuffle();
    // The shuffled deck will display on the screen.
    cout << " Shuffled Deck" << endl;
    deck.display();
    // 26 games will be played, announcing the winner of each game. Ties are possible as well.
    for (int i = 1; i <= 26; i++) {
        cout << "Game " << i << endl;
        cout << "--------" << endl;

        Card p1Card = deck.deal();
        Card p2Card = deck.deal();
        cout << '\t' << player1Name << "=>";
        p1Card.display();
        cout << endl;
        cout << '\t' << player2Name << "=>";
        p2Card.display();
        cout << endl;

        int result = p1Card.compare(p2Card);

        if (!result) {
            cout << "Tie game" << endl;
            ties++;
        } else if (result == 1) {
            cout << player1Name << "=> Winner" << endl;
            player1Wins++;
            player2Losses++;
        } else {
            cout << player2Name << "=> Winner" << endl;
            player2Wins++;
            player1Losses++;
        }
        cout << endl;
    }
    // After all 26 games are played the program will print the statistics.
    cout << "------Final Stats-------" << endl;
    cout << setw(7) << left << ' ' << player1Name << " vs. " << player2Name << endl;
    cout << left << setw(7) << "Wins" << setw(player1Name.length() + 5) << player1Wins << player2Wins << endl;
    cout << left << setw(7) << "Losses" << setw(player1Name.length() + 5) << player1Losses << player2Losses << endl;
    cout << left << setw(7) << "Ties" << setw(player1Name.length() + 5) << ties << ties << endl;

    return 0;
}
