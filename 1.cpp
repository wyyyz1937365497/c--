#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int num_len, num_turn;
    cin >> num_len >> num_turn;
    vector<int> num_list(num_len);
    if (num_len >= num_turn)
    {
        ;
    }
    else
    {
        num_turn = num_turn % num_len;
    }
    for (int i = 0; i < num_len; i++)
    {
        if (i + num_turn < num_len)
        {
            cin >> num_list[i + num_turn];
        }
        else
        {
            cin >> num_list[i + num_turn - num_len];
        }
    }

    for (int i : num_list)
    {
        cout << i << " ";
    }
    cout << endl;
}