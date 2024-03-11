// Aiden Perkins
// CECS 325-02
// Prog 3 – BubbleSort
// Due 3-12-2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Did not provide 3 arguments." << endl;
        return 0;
    }
    srand(time(nullptr));
    ofstream numbersFile("numbers.dat");
    int min = stoi(argv[2]);
    int mod = stoi(argv[3]) - min + 1;
    for (int i = 0; i < stoi(argv[1]); i++) {
        numbersFile << rand() % mod + min << '\n';
    }
    return 0;
}
