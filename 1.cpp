#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;
vector<int> split(const string &str);
int main()
{
    int num_length, query_length;
    cin >> num_length >> query_length;
    cin.get();
    vector<int> num_list;
    vector<int> query_list;
    vector<int> answer;
    num_list.resize(num_length);
    query_list.resize(query_length);
    answer.resize(query_length);
    string input;
    getline(cin, input);
    num_list = split(input);
    getline(cin, input);
    query_list = split(input);
    sort(num_list.begin(), num_list.end());
    for (int i = 0; i < query_length; i++)
    {
        int destanse = query_list[i];
        int length = 0;
        for (int j = 0; j < num_length; j++)
        {
            if (num_list[j] <= destanse)
            {
                length++;
                destanse = destanse - num_list[j];
            }
            else
            {
                break;
            }
        }
        answer[i] = length;
    }
    for (int x : answer)
    {
        cout << x << " ";
    }
    cout << endl;
}
vector<int> split(const string &str)
{
    vector<int> result;
    istringstream iss(str);
    string word;
    while (iss >> word)
    {
        result.push_back(stoi(word));
    }
    return result;
}