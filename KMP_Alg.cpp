#include <bits/stdc++.h>
using namespace std;

// Function to compute the longest prefix suffix (LPS) array for the pattern
void computeLPSArray(char* pat, int M, int* lps) {
    int len = 0; // Length of the previous longest prefix suffix
    lps[0] = 0;  // LPS of the first character is always 0

    // Iterate through the pattern to fill the LPS array
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1]; // Update len using the previous LPS values
            } else {
                lps[i] = 0; // No proper prefix which is also a suffix
                i++;
            }
        }
    }
}

// Function to perform Knuth-Morris-Pratt (KMP) pattern searching
void KMPSearch(char* pat, char* txt) {
    int M = strlen(pat); // Length of the pattern
    int N = strlen(txt); // Length of the text

    int lps[M]; // Array to store longest prefix suffix values

    // Preprocess the pattern to calculate the LPS array
    computeLPSArray(pat, M, lps);

    int i = 0; // Index for traversing the text
    int j = 0; // Index for traversing the pattern

    // Traverse through the text using the KMP algorithm
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            // Found a pattern match at index (i - j) in the text
            printf("Found pattern at index %d\n", i - j);
            j = lps[j - 1]; // Move j to the previous longest prefix suffix
        } else if (i < N && pat[j] != txt[i]) {
            // Mismatch after j matches
            if (j != 0)
                j = lps[j - 1]; // Move j to the previous longest prefix suffix
            else
                i = i + 1; // Move to the next character in the text
        }
    }
}

// Driver code
int main() {
    char txt[] = "I LOVE CPT212"; // Text where pattern is to be searched
    char pat[] = "LOVE";       // Pattern to be searched for in the text

    KMPSearch(pat, txt); // Call the KMP search function

    return 0;
}
