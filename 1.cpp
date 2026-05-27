#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>
using namespace std;

// 使用BFS计算从start节点出发，距离不超过6的节点数

int main()
{
    int vilage_number;
    cin >> vilage_number;
    vector<vector<int>> distance_graph(vilage_number, (vector<int>(vilage_number, 0)));
    vector<vector<int>> road_graph(vilage_number, (vector<int>(vilage_number, 0)));

    for (int i = 0; i < vilage_number; i++)
    {
        for (int j = 0; j, vilage_number; j++)
        {
            cin >> distance_graph[i][j];
        }
    }
    int already_road;
    cin >> already_road;
    for (int i = 0; i < already_road; i++)
    {
        int node_1, node_2;
        cin >> node_1 >> node_2;
        road_graph[node_1 - 1][node_2 - 1] = 1;
        road_graph[node_2 - 1][node_1 - 1] = 1;
    }

    return 0;
}