#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    int number = 0;
    cin >> number;
    vector<int> number_list(number);
    for (int i = 0; i < number; i++)
    {
        cin >> number_list[i];
    }
    sort(number_list.begin(), number_list.end());
}