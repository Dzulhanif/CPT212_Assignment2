#include <iostream>
#include <string>
using namespace std;

#define NO_OF_CHARS 256

// Function to preprocess the bad character table
void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]) {
    // Initialize all occurrences with the pattern length
    for (int i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = size;

    // Update the actual value of the jump length for each character in the pattern
    for (int i = 0; i < size - 1; i++)
        badchar[(int)str[i]] = size - 1 - i;
}

// Function to search for pattern using bad character heuristic
void search(string txt, string pat) {
    int m = pat.size();
    int n = txt.size();
    int badchar[NO_OF_CHARS];

    // Fill the bad character array by calling preprocessing function
    badCharHeuristic(pat, m, badchar);

    // Print the bad character table
    cout << "Bad Character Table:" << endl;
    for (int i = 0; i < NO_OF_CHARS; i++) {
        if (badchar[i] != m) {
            cout << "    " << (char)i << " -> " << badchar[i] << endl;
        }
    }
    cout << "    Last letter '" << pat[m - 1] << "' -> " << badchar[(int)pat[m - 1]] << endl;
    cout << "    * -> " << badchar['*'] << endl; // Ensure * is printed
    cout << endl;


		//define wether string has match or not 
    int s = 0; // s is shift of the pattern with respect to text
    bool found = false; // flag to track if a match is found

    while (s <= (n - m)) {
        int j = m - 1;

        // Keep reducing index j of pattern while characters match
        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        // If the pattern is present at current shift
        if (j < 0) {
            cout << "Pattern occurs at shift = " << s << endl;
            found = true;

            // Shift the pattern to the right
            s += (s + m < n) ? m : 1;
        } else {
            // Shift the pattern so that the bad character in text aligns with the last occurrence of it in pattern
            s += badchar[txt[s + j]];
        }
    }

    // If no match is found, print "No matching"
    if (!found) {
        cout << "=\tNo matching" << endl;
    }
}

// Main code 
int main() {
    string txt = "SELAMAT DATANG KE USM APEX!";
    string pat = "USM";
    search(txt, pat);
    return 0;
	 }

