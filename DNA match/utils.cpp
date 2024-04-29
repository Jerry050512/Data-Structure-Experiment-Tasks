#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <functional>
#include <chrono>
#include <set>

using namespace std;

struct DNAPair
{
    string virus;
    string human;

    DNAPair() {}
    DNAPair(string virus, string human) :  virus(virus), human(human) {}
};

vector<DNAPair> readFromCSV(const string &filename)
{
    vector<DNAPair> data;
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Could not open the file: " << filename << endl;
        return data;
    }

    string line, word;
    getline(file, line);
    int cnt=0;
    while (getline(file, line))
    {
        stringstream s(line);
        DNAPair p;
        getline(s, p.virus, ',');
        s >> p.human;
        data.push_back(p);
        cnt++;
    }
    file.close();
    cout << "Read " << cnt << " pairs from " << filename << endl;
    cout << "Finish reading " << filename << endl;

    return data;
}

void saveToCSVwithResult(vector<pair<bool, DNAPair>> data, const string &filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Failed to open file " << filename << endl;
        return;
    }

    file << "result,virus,human" << endl;

    for (auto &pair : data)
    {
        file << (pair.first ? "true" : "false") << "," << pair.second.virus << "," << pair.second.human << endl;
    }
    file.close();
    cout << "Wrote " << data.size() << " pairs to " << filename << endl;
}

set<string> gen_unique_patterns(string virus_dna)
{
    set<string> patterns;
    patterns.insert(virus_dna);
    int n = virus_dna.length();
    for (int i = 1; i < n; i++)
    {
        patterns.insert(virus_dna.substr(i) + virus_dna.substr(0, i));
    }
    return patterns;
}

using SearchFunction = function<bool(const string &, const string &)>;

long long test_search_function(const vector<DNAPair> &data, SearchFunction search_func)
{
    vector<pair<bool, DNAPair>> results;
    auto start = chrono::high_resolution_clock::now();

    for (const auto &p : data)
    {
        pair<bool, DNAPair> result{false, p};
        auto match_patterns = gen_unique_patterns(p.virus);
        for (const auto &pattern : match_patterns)
        {
            if (search_func(p.human, pattern))
            {
                result.first = true;
                break;
            }
        }
        results.push_back(result);
    }

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

// int main()
// {
//     vector<DNAPair> data = readFromCSV("test_data/input.csv");
//     cout << data[0].virus << " " << data[0].human << endl;
//     vector<pair<bool, DNAPair>> results;
//     pair<bool, DNAPair> test {true, data[0]};
//     results.push_back(test);
//     saveToCSVwithResult(results, "test_data/output.csv");
//     return 0;
// }