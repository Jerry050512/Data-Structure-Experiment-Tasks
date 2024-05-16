#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <cstdio>
#include <climits>

using namespace std;

struct Node {
    char symbol;
    int frequency;
    int parent;
    int left;
    int right;

    Node(char sym, int freq) : 
    	symbol(sym), 
        frequency(freq), 
        parent(-1), 
        left(-1), 
        right(-1) 
    {}
};

class HuffmanTable {
private:
    vector<Node> nodes;
    unordered_map<char, string> codes;

    pair<int, int> getMinTwo() {
        int min1 = INT_MAX, min2 = INT_MAX;
        int min1_index = -1, min2_index = -1;
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].frequency < min1 && nodes[i].parent == -1) {
                min2 = min1;
                min2_index = min1_index;
                min1 = nodes[i].frequency;
                min1_index = i;
            } else if (nodes[i].frequency < min2 && nodes[i].parent == -1) {
                min2 = nodes[i].frequency;
                min2_index = i;
            }
        }
        return make_pair(min1_index, min2_index);
    }

    void buildCodes(Node node, string code="") {
        if (node.symbol != '\0') {
            codes[node.symbol] = code;
        } else {
            if(node.left != -1)
                buildCodes(nodes[node.left], code + "0");
            if(node.right != -1)
            	buildCodes(nodes[node.right], code + "1");
        }
    }

public:
    HuffmanTable(const vector<pair<char, int>>& frequencies) {
        int n = frequencies.size();
        for (int i = 0; i < n; i++) {
            nodes.push_back(Node(frequencies[i].first, frequencies[i].second));
        }
        for(int i=0; i<n-1; i++) {
            pair<int, int> minTwo = getMinTwo();
            Node parent = Node(
                            '\0', 
                            nodes[minTwo.first].frequency + nodes[minTwo.second].frequency
                        );
            parent.left = minTwo.first;
            parent.right = minTwo.second;
            nodes.push_back(parent);
            nodes[minTwo.first].parent = nodes.size()-1;
            nodes[minTwo.second].parent = nodes.size()-1;
        }
        buildCodes(nodes[nodes.size()-1]);
    }

    // encode : Look up in the codes table
    string encode(const string& text) {
        string encoded;
        for (char c : text) {
            encoded += codes[c];
        }
        return encoded;
    }

    // decode : Traverse the tree and decode the encoded text
    string decode(const string& encoded) {
        string decoded;
        Node curr = nodes[nodes.size()-1];
        for (char bit : encoded) {
            if (bit == '0') {
                curr = nodes[curr.left];
            } else {
                curr = nodes[curr.right];
            }

            if (curr.symbol != '\0') {
                decoded += curr.symbol;
                curr = nodes[nodes.size()-1];
            }
        }
        return decoded;
    }

    void showTable() {
        for (int i = 0; i < nodes.size(); i++) {
            cout << (nodes[i].symbol == '\0' ? '#' : nodes[i].symbol) << " " << nodes[i].frequency << " "
            << nodes[i].parent << " " << nodes[i].left << " " << nodes[i].right 
            << endl;
        }
    }

    void showCodes() {
        for (const auto& pair : codes) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }
};


vector<pair<char, int>> buildFrequencies(const string& str) {
    vector<pair<char, int>> freq;
    unordered_map<char, int> count;

    // Default value for int is 0
    for (char c : str) {
        count[c]++;
    }

    for (const auto& pair : count) {
        freq.push_back(pair);
    }

    return freq;
}

int main() {
string input;
    while(true) {
        cout << "Enter a string (0 to exit): ";
        getline(cin, input);
        if (input == "0") break;

        vector<pair<char, int>> frequencies = buildFrequencies(input);
        HuffmanTable huffman(frequencies);

        cout << "Frequencies: " << endl;
        for (const auto& pair : frequencies) {
            cout << pair.first << ": " << pair.second << endl;
        }

        cout << "Huffman Table: " << endl;
        huffman.showTable();

        cout << "Code Map: " << endl;
        huffman.showCodes();

        string encoded = huffman.encode(input);
        cout << "Encoded text: " << encoded << endl;

        string decoded = huffman.decode(encoded);
        cout << "Decoded text: " << decoded << endl;
    }
}