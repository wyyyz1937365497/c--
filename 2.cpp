#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>
using namespace std;

// 使用BFS计算从start节点出发，距离不超过6的节点数
int count_within_6(int start, const vector<vector<int>> &adj_list)
{
    int n = adj_list.size();
    vector<bool> visited(n, false);
    queue<pair<int, int>> q; // pair<节点编号, 距离>

    q.push({start, 0});
    visited[start] = true;
    int count = 1; // 包含起始节点自己

    while (!q.empty())
    {
        int node = q.front().first;
        int distance = q.front().second;
        q.pop();

        // 如果距离已经达到6，不再继续扩展
        if (distance >= 6)
        {
            continue;
        }

        // 只遍历实际存在的邻居（使用邻接表）
        for (int neighbor : adj_list[node])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push({neighbor, distance + 1});
                count++;
            }
        }
    }

    return count;
}

int main()
{
    int node_number, edge_number;
    cin >> node_number >> edge_number;

    // 使用邻接表存储图（节点编号从0开始存储）
    vector<vector<int>> adj_list(node_number);

    for (int i = 0; i < edge_number; i++)
    {
        int node_1, node_2;
        cin >> node_1 >> node_2;
        // 输入节点编号从1开始，转换为从0开始
        node_1--;
        node_2--;
        adj_list[node_1].push_back(node_2);
        adj_list[node_2].push_back(node_1);
    }

    // 对每个节点计算距离不超过6的节点数并输出百分比
    for (int i = 0; i < node_number; i++)
    {
        int count = count_within_6(i, adj_list);
        float percentage = (float)count / node_number * 100.0;
        cout << (i + 1) << ": " << fixed << setprecision(2) << percentage << "%" << endl;
    }

    return 0;
}