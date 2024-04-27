#include <iostream>
#include <unordered_set>

using namespace std;

int eliminateDuplicates(char letters[], int length) {
    unordered_set<char> seenCharacters;
    int newIndex = 0;

    for (int i = 0; i < length; ++i) {
        if (seenCharacters.insert(letters[i]).second) {
            letters[newIndex++] = letters[i];
        }
    }

    return newIndex;
}

int main() {
    char letters[150]; // Array size for a wider range of input
    int length = 0;
    char currentChar;
    cout << "Input characters (type '#' to finish): "; // Updated message

    while (cin >> currentChar && currentChar != '#') { // Changed to '#' as the stop character
        if (length < 150) {
            letters[length++] = currentChar;
        } else {
            cout << "Maximum capacity reached." << endl;
            break;
        }
    }

    int updatedSize = eliminateDuplicates(letters, length);

    cout << "the output without duplicates is: ";
    for (int i = 0; i < updatedSize; ++i) {
        cout << letters[i] << " ";
    }
    cout << endl;

    return 0;
}




