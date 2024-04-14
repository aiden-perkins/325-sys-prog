#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include <cmath>

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

struct Bucket {
    int* ptr;  // a pointer to the start of this bucket
    int size;  // the size of the bucket
};

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
    if (argc != 4) {
        cout << "Did not provide 3 arguments, stopping" << endl;
        return 0;
    }

    const int MAX_NUMS = 1000000;

    string inFl = argv[1];
    string otFl = argv[2];
    int bucketSize = stoi(argv[3]);
    cout << "Input File: " << inFl << endl;
    cout << "Output File: " << otFl << endl;
    cout << "Bucket Size: " << bucketSize << endl;

    int index = -1;
    int* nums = new int[MAX_NUMS];
    ifstream inputFile(inFl);
    while (inputFile >> nums[++index]) {
        if (index + 1 > MAX_NUMS) {
            cout << "Input file has more than " << MAX_NUMS << " numbers, killing program." << endl;
            delete [] nums;
            return 0;
        }
    }
    int bucketCount = ceil(double(index) / bucketSize);
    cout << "Input Count: " << index << endl;
    cout << "Total Bucket Count: " << bucketCount << endl;

    vector<Bucket> bucketList;
    vector<thread> threadList;
    for (int i = 0; i < bucketCount; ++i) {
        int s = bucketSize;
        if (i == bucketCount - 1) {
            s = index - (i * bucketSize);
        }
        Bucket temp{nums + (i * bucketSize), s};
        bucketList.push_back(temp);
        threadList.emplace_back(bubble, nums + (i * bucketSize), s);
    }
    for (int i = 0; i < bucketCount; ++i) {
        threadList[i].join();
    }

    while (bucketList.size() > 1) {
        for (int i = 0; i < bucketList.size() - 1; ++i) {
            Bucket b1 = bucketList[i];
            Bucket b2 = bucketList[i + 1];
            merge(b1.ptr - 1, b1.ptr + b1.size - 1, b2.ptr - 1, b2.ptr + b2.size - 1);
            bucketList.erase(bucketList.begin() + i + 1);
            bucketList[i].size = b1.size + b2.size;
        }
    }

    ofstream outputFile(otFl);
    for (int i = 0; i < index; ++i) {
        outputFile << nums[i] << '\n';
    }
    delete [] nums;
    return 0;
}
