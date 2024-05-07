#include <iostream>
#include <vector>

using namespace std;

int findMissing(vector<int> &nums)
{
    int n = nums.size();
    int* hash = new int[n];
    for (int i = 0; i < n; i++)
        if(nums[i] > 0 && nums[i] <= n)
            hash[nums[i]-1] = 1;
    for (int i = 0; i < n; i++)
        if (hash[i] == 0)
            return i + 1;
    return n + 1;
}

int main()
{
    vector<int> nums = {-1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15};
    cout << findMissing(nums) << endl;
    return 0;
}