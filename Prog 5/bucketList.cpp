// Aiden Perkins
// CECS 325-02
// Prog 5 – BucketList (vectors)
// Due 4-23-2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int globalSwapCount = 0;

class Bucket {
    private:
        vector<int> _nums;
        int _size = 0;
    public:
        Bucket() = default;

        void generate(int size, int min, int max) {
            _size = size;
            int mod = max - min + 1;
            for (int i = 0; i < size; i++) {
                _nums.push_back(rand() % mod + min);
            }
        }

        void sort() {  // Use the bubble sort from Prog3 and Prog4
            bool hasSwapped;
            for (int i = 0; i < _size - 1; ++i) {
                hasSwapped = false;
                for (int j = 0; j < _size - i - 1; ++j) {
                    if (_nums[j + 1] < _nums[j]) {
                        int temp = _nums[j + 1];
                        _nums[j + 1] = _nums[j];
                        _nums[j] = temp;
                        globalSwapCount++;
                        hasSwapped = true;
                    }
                }
                if (!hasSwapped) {
                    break;
                }
            }
        }

        int size() const {
            return _size;
        }

        int atIndex(int idx) {
            return _nums[idx];
        }

        int merge(Bucket b) {  // merge b into this
            vector<int> merged;
            int i = 0, j = 0;
            while (i < _size && j < b.size()) {
                if (_nums[i] <= b.atIndex(j)) {
                    merged.push_back(_nums[i]);
                    i++;
                } else {
                    merged.push_back(b.atIndex(j));
                    j++;
                }
            }
            while (i < _size) {
                merged.push_back(_nums[i]);
                i++;
            }
            while (j < b.size()) {
                merged.push_back(b.atIndex(j));
                j++;
            }
            _size = int(merged.size());
            _nums = merged;
            return _size;
        }
};

// usage: $ bucketList 100 100 1000000 9000000
// bucketList bucketCount bucketSize min max
int main(int argc, char* argv[]) {

    srand(time(nullptr));
    int bucketCount = stoi(argv[1]);
    int bucketSize = stoi(argv[2]);
    int bucketMin = stoi(argv[3]);
    int bucketMax = stoi(argv[4]);

    cout << "Bucket Count:" << bucketCount << endl;
    cout << "Bucket Size:" << bucketSize << endl;
    cout << "Bucket Min Value:" << bucketMin << endl;
    cout << "Bucket Max value:" << bucketMax << endl;

    vector<Bucket> bucketList; // create empty Bucket vector
    Bucket* bptr;

    for (int i = 0; i < bucketCount; i++) {  // creating bucketCount Buckets
        bptr = new Bucket;  // allocating new Bucket
        bptr->generate(bucketSize, bucketMin, bucketMax);  // Bucket::generate(int,int,int,int)
        bucketList.push_back(*bptr);  // pushing Bucket onto list
        // delete bptr;
    }
    for (auto it = bucketList.begin(); it != bucketList.end(); it++) {
        it->sort();  // Bucket::sort
    }
    Bucket endGame;  // create empty Bucket to merge ALL buckets
    while (!bucketList.empty()) {  // vector<Bucket>::size()
        endGame.merge(bucketList[0]);  // merge first bucket in list into endGame
        bucketList.erase(bucketList.begin());  // erase the first bucket in the list
    }
    // write all the numbers in endGame bucket to a file
    fstream out("bucketList.out", ios::out);
    for (int i = 0; i < endGame.size(); i++) {  // Bucket::size()
        out << endGame.atIndex(i) << endl;  // Bucket::atIndex(int)
    }

    cout << "Global Swap Count:" << globalSwapCount << endl;
    cout << endl;
    cout << "bucketList.out has " << bucketCount * bucketSize << " sorted numbers" << endl;
    return 0;
}