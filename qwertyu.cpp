#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int number = 0;
    if (!(cin >> number))
        return 0;

    vector<int> number_list(number);
    vector<vector<int>> output_list;
    for (int i = 0; i < number; i++)
    {
        cin >> number_list[i];
    }
    sort(number_list.begin(), number_list.end());
    for (int i = 0; i < number - 2; i++)
    {
        if (number_list[i] > 0)
            break;
        if (i > 0 && number_list[i] == number_list[i - 1])
        {
            continue;
        }

        int left = i + 1;
        int right = number - 1;
        while (left < right)
        {
            int sum = number_list[i] + number_list[left] + number_list[right];
            if (sum == 0)
            {
                output_list.push_back({number_list[i], number_list[left], number_list[right]});

                // 修正3：跳过重复元素后，必须再移动一次指针
                while (left < right && number_list[left] == number_list[left + 1])
                    left++;
                while (left < right && number_list[right] == number_list[right - 1])
                    right--;
                left++;
                right--;
            }
            else if (sum > 0)
            {
                right--;
            }
            else
            {
                left++;
            }
        }
    }
    for (const auto &triplet : output_list)
    {
        cout << triplet[0] << " " << triplet[1] << " " << triplet[2] << endl;
    }
    return 0;
}