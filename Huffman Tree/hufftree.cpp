#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <cstdio>

using namespace std;

struct Node {
    char symbol;
    int frequency;
    Node* left;
    Node* right;

    Node(char sym, int freq) : symbol(sym), frequency(freq), left(nullptr), right(nullptr) {}
};

class HuffmanTree {
private:
    Node* root;
    // Huffman Code Lookup Table
    unordered_map<char, string> codes;

	// Build Table
    void buildCodes(Node* node, string code="") {
        if (!node) return;

        if (node->symbol != '\0') {
            codes[node->symbol] = code;
        } else {
            buildCodes(node->left, code + "0");
            buildCodes(node->right, code + "1");
        }
    }

public:
    HuffmanTree(const vector<pair<char, int>>& frequencies) {
        // Use priority queue to sort nodes by frequency
        priority_queue<Node*, vector<Node*>, CompareFrequency> pq;

        for (const auto& pair : frequencies) {
            pq.push(new Node(pair.first, pair.second));
        }

        while (pq.size() > 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();

            Node* parent = new Node('\0', left->frequency + right->frequency);
            parent->left = left;
            parent->right = right;

            pq.push(parent);
        }

        root = pq.top();
        buildCodes(root);
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
        Node* curr = root;
        for (char bit : encoded) {
            if (bit == '0') {
                curr = curr->left;
            } else {
                curr = curr->right;
            }

            if (curr->symbol != '\0') {
                decoded += curr->symbol;
                curr = root;
            }
        }
        return decoded;
    }

    void showCodes() {
        for (const auto& pair : codes) {
            cout << pair.first << ": " << pair.second << endl;
        }
    }

private:
    // Compare Frequency used in priority queue
    struct CompareFrequency {
        bool operator()(Node* a, Node* b) {
            return a->frequency > b->frequency;
        }
    };
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
        HuffmanTree huffman(frequencies);

        cout << "Code Map: " << endl;
        huffman.showCodes();

        string encoded = huffman.encode(input);
        cout << "Encoded text: " << encoded << endl;

        string decoded = huffman.decode(encoded);
        cout << "Decoded text: " << decoded << endl;
    }

    return 0;
}