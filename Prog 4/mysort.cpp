// Aiden Perkins
// CECS 325-02
// Prog 4 – Sorting Contest using pThreads
// Due 3-26-2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

void bubble(int A[], int size) {
    bool hasSwapped;
    for (int i = 0; i < size - 1; ++i) {
        hasSwapped = false;
        for (int j = 0; j < size - i - 1; ++j) {
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

struct partialNums {
    int* startAddress;
    int amount;
};

void* bridge(void* voidPtr) {
    auto* pnPtr = (partialNums*) voidPtr;
    bubble(pnPtr -> startAddress, pnPtr -> amount);
    return nullptr;
}

void merge(int* fs, const int* fe, int* ss, int* se) {
    int newSize = int(se - fs);
    int newArr[newSize];
    for (int i = 0; i < newSize; ++i) {
        if ((*(fs + 1) < *(ss + 1) && (fs + 1 <= fe)) || (ss + 1 > se)) {
            newArr[i] = *(++fs);
        } else {
            newArr[i] = *(++ss);
        }
    }
    for (int i = 0; i < newSize; ++i) {
        se[-i] = newArr[newSize - i - 1];
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Did not provide 2 arguments" << endl;
        return 0;
    }

    const int MAX_NUMS = 1000000;
    // The threads used in this program is 2^TWO_POWER so for 8 threads, TWO_POWER = 3 as 2^3 = 8.
    const int TWO_POWER = 3;  // On my 8 core/16 thread AMD 1800x cpu, the max I can make this variable is 11 as 12 and up breaks everything.
    const int THREAD_COUNT = int(pow(2, TWO_POWER));

    int index = -1;
    int* nums = new int[MAX_NUMS];
    ifstream inputFile(argv[1]);
    while (inputFile >> nums[++index]);

    // This is so the amount of numbers in the input file doesn't have to be a multiple of the amount of threads for this to still work.
    int onePart = ceil(double(index) / THREAD_COUNT);
    int lastSize = index - ((THREAD_COUNT - 1) * onePart);
    int lastDifference = onePart - lastSize;

    pthread_t threads[THREAD_COUNT];
    partialNums pns[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; ++i) {
        pns[i] = partialNums{nums + (onePart * i), onePart};
        if (i == THREAD_COUNT - 1) {
            pns[i].amount = lastSize;
        }
        pthread_create(&threads[i], nullptr, bridge, (void*) &pns[i]);
    }

    for (int i = 0; i < THREAD_COUNT; ++i) {
        pthread_join(threads[i], nullptr);
    }

    for (int i = 1; i < TWO_POWER + 1; ++i) {
        for (int j = 0; j < pow(2, TWO_POWER - i); ++j) {
            int start = j * (onePart * int(pow(2, i - 1))) * 2;
            int middle = start + (onePart * int(pow(2, i - 1)));
            int end = start + (onePart * int(pow(2, i - 1)) * 2);
            if (j == pow(2, TWO_POWER - i) - 1) {
                end -= lastDifference;
            }
            merge(nums + start - 1, nums + middle - 1, nums + middle - 1, nums + end - 1);
        }
    }

    ofstream outputFile(argv[2]);
    for (int i = 0; i < index; ++i) {
        outputFile << nums[i] << '\n';
    }
    delete [] nums;
}
