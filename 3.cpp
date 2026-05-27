#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Prim算法求最小生成树
int prim(int n, vector<vector<int>> &graph, const vector<pair<int, int>> &existing_edges)
{
    // dist[i] 表示节点i到当前生成树的最小距离
    vector<int> dist(n, INT_MAX);
    // visited[i] 表示节点i是否已加入生成树
    vector<bool> visited(n, false);

    // 将已存在的边的权值设为0
    for (const auto &edge : existing_edges)
    {
        int u = edge.first;
        int v = edge.second;
        graph[u][v] = 0;
        graph[v][u] = 0;
    }

    // 从节点0开始
    dist[0] = 0;
    int total_cost = 0;

    for (int i = 0; i < n; i++)
    {
        // 找到未访问节点中距离最小的
        int min_dist = INT_MAX;
        int u = -1;
        for (int j = 0; j < n; j++)
        {
            if (!visited[j] && dist[j] < min_dist)
            {
                min_dist = dist[j];
                u = j;
            }
        }

        // 将节点u加入生成树
        visited[u] = true;
        total_cost += dist[u];

        // 更新与u相邻的节点的距离
        for (int v = 0; v < n; v++)
        {
            if (!visited[v] && graph[u][v] < dist[v])
            {
                dist[v] = graph[u][v];
            }
        }
    }

    return total_cost;
}

int main()
{
    int n;
    cin >> n;

    // 读取距离矩阵
    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
    }

    // 读取已存在的边
    int m;
    cin >> m;
    vector<pair<int, int>> existing_edges(m);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        // 转换为从0开始的编号
        existing_edges[i] = {a - 1, b - 1};
    }

    // 使用Prim算法计算最小生成树的总权值
    int result = prim(n, graph, existing_edges);

    cout << result << endl;

    return 0;
}