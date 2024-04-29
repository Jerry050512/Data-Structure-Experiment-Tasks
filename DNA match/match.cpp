#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool bf_search(const string &text, const string &pattern)
{
    int text_len = text.length();
    int pattern_len = pattern.length();
    for(int i=0; i < text_len-pattern_len+1; i++)
    {
        for(int j=0; j < pattern_len; j++)
        {
            if(text[i+j] != pattern[j])
            {
                break;
            }
            if(j == pattern_len-1)
            {
                return true;
            }
        }
    }
    return false;
}

// Function to compute the Longest Prefix Suffix (LPS) array
vector<int> compute_lps(const string &pattern)
{
    int length = 0; // length of the previous longest prefix suffix
    int i = 1;
    vector<int> lps(pattern.length(), 0);

    // lps[0] is always 0
    while (i < pattern.length())
    {
        if (pattern[i] == pattern[length])
        {
            length++;
            lps[i] = length;
            i++;
        }
        else
        {
            if (length != 0)
            {
                length = lps[length - 1];
            }
            else
            {
                lps[i] = 0; // Or lps[i] = length;
                i++;
            }
        }
    }

    return lps;
}

// KMP search algorithm
bool kmp_search(const string &text, const string &pattern)
{
    vector<int> lps = compute_lps(pattern);

    int i = 0; // index for text[]
    int j = 0; // index for pattern[]
    while (i < text.length())
    {
        if (pattern[j] == text[i])
        {
            j++;
            i++;
        }

        if (j == pattern.length())
        {
            // pattern found at index i - j
            return true;
            j = lps[j - 1];
        }
        else if (i < text.length() && pattern[j] != text[i])
        {
            // mismatch after j matches
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    return false;
}