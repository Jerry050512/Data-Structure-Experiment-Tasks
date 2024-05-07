#include <iostream>
#include <vector>

using namespace std;

int findMidNum(vector<int> &a, vector<int> &b)
{
    if(a.size() != b.size()) return -1;

    int length = a.size();
    int i=0, j=0;
    while(i + j < length - 1)
    {
        if(a[i] < b[j])
        {
            i++;
        }
        else
        {
            j++;
        }
    }

    return a[i] < b[j] ? a[i] : b[j];
}

int main()
{
    vector<int> a = {11, 13, 15, 17, 19};
    vector<int> b = {2, 4, 6, 8, 20};

    cout << findMidNum(a, b) << endl;
}