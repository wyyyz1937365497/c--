/**
 * @file    template.cpp
 * @name    模板程序
 * @date    2022-11-22
 */

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

/********************************/
/*     以下是你需要提交的代码     */
/********************************/
class Solution
{
public:
    std::string largestNumber(std::vector<int> &nums)
    {
        string output;
        sort(nums.begin(), nums.end(), [](const int &a, const int &b)
             { 
         string sa = to_string(a);
         string sb = to_string(b);
         return sa + sb > sb + sa; });
        for (int x : nums)
        {
            output += to_string(x);
        }
        return output;
    }
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> nums[i];
    }
    Solution s;
    std::cout << s.largestNumber(nums) << std::endl;
    return 0;
}