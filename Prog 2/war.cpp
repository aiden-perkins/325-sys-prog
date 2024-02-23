// Aiden Perkins
// CECS 325-02
// Prog 2 – One Card War
// Due 2-27-2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <algorithm>
using namespace std;


class Card {
    private:
        char suit;
        char rank;
    public:
        Card() {}  // default constructor – needed for array in Deck class

        Card(char s, char r) {  // constructor to create a card, setting the suit and rank
            suit = s;
            rank = r;
        }

        void display() const {  // display the card example: AC, 10S, KD
            rank == 'T' ? cout << "10" << suit : cout << rank << suit;
        }

        int compare(Card card) const {  // return 1 for win, 0 for tie, -1 for lose
            map<char, int> rank_map = {
                {'A', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5},
                {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
                {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}
            };
            return (rank == card.rank ? 0 : (rank_map[rank] > rank_map[card.rank] ? 1 : -1));
        }
};

class Deck {
    private:
        Card cards[52];
        int backOfDeck;
    public:
        Deck() {  // constructor which creates a deck of 52 cards
            backOfDeck = 51;
            char suits[4] = {'C', 'S', 'D', 'H'};
            char ranks[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
            for (int i = 0; i < 52; i++) cards[i] = Card(suits[i / 13], ranks[i % 13]);
        }

        Card deal() {  // deal a card
            if (isEmpty()) throw "Deck is empty";
            Card card = cards[backOfDeck];
            backOfDeck--;
            return card;
        }

        void display() {  // show all the cards in the deck
            for (int i = 0; i < 52; i++) {
                cards[i].display();
                cout << ((i + 1) % 13 ? ',' : '\n');
            }
        }

        void shuffle() {  // shuffle the cards in the deck
            srand(time(nullptr));
            for (int i = 0; i < 10000; i++) {
                int rand_value_1 = rand() % 52;
                int rand_value_2 = rand() % 52;
                Card temp = cards[rand_value_1];
                cards[rand_value_1] = cards[rand_value_2];
                cards[rand_value_2] = temp;
            }
        }

        bool isEmpty() const {  // return true if deck is empty
            return backOfDeck < 0;
        }
};

int main() {
    // A new deck will be created.
    Deck deck;
    // The program will ask for the names of the 2 players.
    int ties = 0;
    string player1Name;
    int player1Wins = 0;
    int player1Losses = 0;
    cout << "Enter the name of the first player: ";
    cin >> player1Name;
    string player2Name;
    int player2Wins = 0;
    int player2Losses = 0;
    cout << "Enter the name of the second player: ";
    cin >> player2Name;
    // The program will ask how many games you want to play.
    int gamesToPlay;
    cout << "How many games will they play? ";
    cin >> gamesToPlay;
    cout << endl;
    // The un-shuffled deck will be displayed on the screen.
    cout << " Original Deck" << endl;
    deck.display();
    cout << endl;
    // The deck will be shuffled.
    deck.shuffle();
    // The shuffled deck will display on the screen.
    cout << " Shuffled Deck" << endl;
    deck.display();
    // 26 games will be played, announcing the winner of each game. Ties are possible as well.
    for (int i = 1; i <= gamesToPlay; i++) {
        try {
            Card p1Card = deck.deal();
            Card p2Card = deck.deal();
            cout << endl;
            cout << "Game " << i << endl;
            cout << "--------" << endl;
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
        } catch (const char* error) {
            cout << "Error - " << error << endl;
            break;
        }
    }
    // After all 26 games are played the program will print the statistics.
    cout << "------Final Stats-------" << endl;
    cout << setw(7) << left << ' ' << player1Name << " vs. " << player2Name << endl;
    cout << left << setw(7) << "Wins" << setw(int(player1Name.length()) + 5) << player1Wins << player2Wins << endl;
    cout << left << setw(7) << "Losses" << setw(int(player1Name.length()) + 5) << player1Losses << player2Losses << endl;
    cout << left << setw(7) << "Ties" << setw(int(player1Name.length()) + 5) << ties << ties << endl;

    return 0;
}
