#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void bubble(int A[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (A[j + 1] < A[j]) {
                swap(A[j + 1], A[j]);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Did not provide 2 arguments" << endl;
        return 1;
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
    }
    bubble(A, index);
    ofstream outputFile(argv[2]);
    for (int i = 0; i < index; i++) {
        outputFile << A[i] << endl;
    }
}
