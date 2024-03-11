// Aiden Perkins
// CECS 325-02
// Prog 3 – BubbleSort
// Due 3-12-2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void bubble(int A[], int size) {
    bool hasSwapped;
    for (int i = 0; i < size - 1; i++) {
        hasSwapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (A[j + 1] < A[j]) {
                int temp = A[j + 1];
                A[j + 1] = A[j];
                A[j] = temp;
                hasSwapped = true;
            }
        }
        if (!hasSwapped) {
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Did not provide 2 arguments" << endl;
        return 0;
    }
    int index = 0;
    int A[1000000];
    ifstream inputFile(argv[1]);
    if (inputFile) {
        string line;
        while (getline(inputFile, line)) {
            A[index] = stoi(line);
            index++;
        }
    } else {
        cout << "Could not open the file " << argv[1] << "" << endl;
        return 0;
    }
    bubble(A, index);
    ofstream outputFile(argv[2]);
    for (int i = 0; i < index; i++) {
        outputFile << A[i] << endl;
    }
}
