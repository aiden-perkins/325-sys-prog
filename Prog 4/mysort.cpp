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

struct partialNums {
    int* startAddress;
    int amount;
};

void* bridge(void* voidPtr) {
    auto* pnPtr = (partialNums*) voidPtr;
    bubble(pnPtr -> startAddress, pnPtr -> amount);
    return nullptr;
}

int merge(const int first[], int firstSize, const int second[], int secondSize, int newArr[]) {
    int f = 0, s = 0;
    for (int i = 0; i < firstSize + secondSize; i++) {
        if ((first[f] < second[s] && f < firstSize) || s >= secondSize) {
            newArr[i] = first[f++];
        } else {
            newArr[i] = second[s++];
        }
    }
    return firstSize + secondSize;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Did not provide 2 arguments" << endl;
        return 0;
    }
    int index = 0;
    int* A = new int[1000000];
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

    int oneEighth = ceil(double(index) / 8);
    // This is so the amount of numbers in the input file doesn't have to be a multiple of 8 for this to still work.
    // I would have liked to go a step further and be able to control how many threads are used but that would require
    // arrays of pthreads and there might be a chance that I lose points in doing so, maybe another time.
    int lastSize = index - (7 * oneEighth);

    pthread_t thread0, thread1, thread2, thread3, thread4, thread5, thread6, thread7;

    partialNums p0{&A[oneEighth * 0], oneEighth};
    partialNums p1{&A[oneEighth * 1], oneEighth};
    partialNums p2{&A[oneEighth * 2], oneEighth};
    partialNums p3{&A[oneEighth * 3], oneEighth};
    partialNums p4{&A[oneEighth * 4], oneEighth};
    partialNums p5{&A[oneEighth * 5], oneEighth};
    partialNums p6{&A[oneEighth * 6], oneEighth};
    partialNums p7{&A[oneEighth * 7], lastSize};

    pthread_create(&thread0, nullptr, bridge, (void*) &p0);
    pthread_create(&thread1, nullptr, bridge, (void*) &p1);
    pthread_create(&thread2, nullptr, bridge, (void*) &p2);
    pthread_create(&thread3, nullptr, bridge, (void*) &p3);
    pthread_create(&thread4, nullptr, bridge, (void*) &p4);
    pthread_create(&thread5, nullptr, bridge, (void*) &p5);
    pthread_create(&thread6, nullptr, bridge, (void*) &p6);
    pthread_create(&thread7, nullptr, bridge, (void*) &p7);

    pthread_join(thread0, nullptr);
    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);
    pthread_join(thread3, nullptr);
    pthread_join(thread4, nullptr);
    pthread_join(thread5, nullptr);
    pthread_join(thread6, nullptr);
    pthread_join(thread7, nullptr);

    int* m1 = new int[p0.amount + p1.amount];
    int m1Size = merge(p0.startAddress, p0.amount, p1.startAddress, p1.amount, m1);
    int* m2 = new int[p2.amount + p3.amount];
    int m2Size = merge(p2.startAddress, p2.amount, p3.startAddress, p3.amount, m2);
    int* m3 = new int[p4.amount + p5.amount];
    int m3Size = merge(p4.startAddress, p4.amount, p5.startAddress, p5.amount, m3);
    int* m4 = new int[p6.amount + p7.amount];
    int m4Size = merge(p6.startAddress, p6.amount, p7.startAddress, p7.amount, m4);
    delete [] A;

    int* m5 = new int[m1Size + m2Size];
    int m5Size = merge(m1, m1Size, m2, m2Size, m5);
    delete [] m1;
    delete [] m2;
    int* m6 = new int[m3Size + m4Size];
    int m6Size = merge(m3, m3Size, m4, m4Size, m6);
    delete [] m3;
    delete [] m4;

    int* m7 = new int[m5Size + m6Size];
    merge(m5, m5Size, m6, m6Size, m7);
    delete [] m5;
    delete [] m6;

    ofstream outputFile(argv[2]);
    for (int i = 0; i < index; i++) {
        outputFile << m7[i] << '\n';
    }
    delete [] m7;
}
