#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

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