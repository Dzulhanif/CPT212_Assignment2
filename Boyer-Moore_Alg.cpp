#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define NO_OF_CHARS 256

// The preprocessing function for Boyer Moore's bad character heuristic
void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]) {
    // Initialize all occurrences as -1
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    // Fill the actual value of last occurrence of a character
    for (int i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

// Preprocessing for the strong good suffix rule
void preprocessStrongSuffix(vector<int>& shift, vector<int>& bpos, string pat, int m) {
    int i = m, j = m + 1;
    bpos[i] = j;

    while (i > 0) {
        while (j <= m && pat[i - 1] != pat[j - 1]) {
            if (shift[j] == 0)
                shift[j] = j - i;
            j = bpos[j];
        }
        i--;
        j--;
        bpos[i] = j;
    }
}

// Preprocessing for case 2
void preprocessCase2(vector<int>& shift, vector<int>& bpos, string pat, int m) {
    int j = bpos[0];
    for (int i = 0; i <= m; i++) {
        if (shift[i] == 0)
            shift[i] = j;
        if (i == j)
            j = bpos[j];
    }
}

// Search for a pattern in given text using Boyer Moore algorithm
void search(string txt, string pat) {
    int m = pat.size();
    int n = txt.size();

    int badchar[NO_OF_CHARS];
    vector<int> bpos(m + 1);
    vector<int> shift(m + 1, 0);

    // Fill the bad character array by calling the preprocessing function
    badCharHeuristic(pat, m, badchar);

    // Do preprocessing for good suffix rule
    preprocessStrongSuffix(shift, bpos, pat, m);
    preprocessCase2(shift, bpos, pat, m);

    int s = 0; // s is shift of the pattern with respect to text

    while (s <= (n - m)) {
        int j = m - 1;

        // Keep reducing index j of pattern while characters of pattern and text are matching at this shift s
        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        // If the pattern is present at the current shift, then index j will become -1 after the above loop
        if (j < 0) {
            cout << "Pattern occurs at the index of = " << s << endl;
            s += shift[0];
        } else {
            // Shift the pattern so that the bad character in text aligns with the last occurrence of it in pattern
            s += max(shift[j + 1], j - badchar[txt[s + j]]);
        }
    }
}

// Driver code
int main() {
    string txt = "EMBUN PAGI YANG SEJUK";
    string pat = "YANG";
    cout << "The whole text: " << txt << endl;
    cout << "The pattern to find: " << pat << endl;
    search(txt, pat);
    return 0;
}
