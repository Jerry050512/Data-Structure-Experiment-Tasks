#include <vector>
#include <iostream>
#include <string>
#include <chrono>
#include <set>

#define DEBUG 1

#include "utils.cpp"
#include "match.cpp"

using namespace std;

int main()
{
    #ifdef DEBUG
    cout << "DEBUG MODE" << endl;
    #endif
    string input_path, output_path;
    cout << "Enter input file path (enter to use default value): ";
    getline(cin, input_path);
    cout << "Enter output file path (enter to use default value): ";
    getline(cin, output_path);
    if(input_path.empty()) input_path = "test_data/input.csv";
    if(output_path.empty()) output_path = "test_data/output.csv";

    vector<DNAPair> data = readFromCSV(input_path);
    vector<pair<bool, DNAPair>> results;

    // Test BF algorithm
    auto start = chrono::high_resolution_clock::now();
    for(auto& p : data)
    {
        pair<bool, DNAPair> result {false, p};
        auto match_patterns = gen_unique_patterns(p.virus);
        for(auto& pattern : match_patterns)
        {
            if(bf_search(p.human, pattern))
            {
                result.first = true;
                break;
            }
        }
        results.push_back(result);
    }
    auto end = chrono::high_resolution_clock::now();
    cout << "BF Alogrithm: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    
    results.clear();

    // Test KMP algorithm
    start = chrono::high_resolution_clock::now();
    for(auto& p : data)
    {
        pair<bool, DNAPair> result {false, p};
        auto match_patterns = gen_unique_patterns(p.virus);
        for(auto& pattern : match_patterns)
        {
            if(kmp_search(p.human, pattern))
            {
                result.first = true;
                break;
            }
        }
        results.push_back(result);
    }
    end = chrono::high_resolution_clock::now();
    cout << "KMP search time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;

    saveToCSVwithResult(results, output_path);
}