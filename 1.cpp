#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

// 使用BFS遍历一个连通分量
void bfs_component(const vector<vector<int>> &graph, int start, vector<bool> &visited, vector<int> &component)
{
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        component.push_back(node);

        // 按编号从小到大访问邻居
        for (int i = 0; i < graph.size(); i++)
        {
            if (graph[node][i] == 1 && !visited[i])
            {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

// 使用DFS遍历一个连通分量（模拟递归行为）
void dfs_component(const vector<vector<int>> &graph, int start, vector<bool> &visited, vector<int> &component)
{
    stack<int> s;
    s.push(start);

    while (!s.empty())
    {
        int node = s.top();

        if (!visited[node])
        {
            // 首次访问该节点
            visited[node] = true;
            component.push_back(node);
        }

        // 寻找下一个未访问的邻居
        int next_unvisited = -1;
        for (int i = 0; i < graph.size(); i++)
        {
            if (graph[node][i] == 1 && !visited[i])
            {
                next_unvisited = i;
                break;
            }
        }

        if (next_unvisited != -1)
        {
            // 找到未访问邻居，深入探索
            s.push(next_unvisited);
        }
        else
        {
            // 所有邻居都已访问，回溯
            s.pop();
        }
    }
}

// 打印连通分量
void print_components(const vector<vector<int>> &components)
{
    for (const auto &comp : components)
    {
        cout << "{";
        for (int i = 0; i < comp.size(); i++)
        {
            if (i > 0)
                cout << " ";
            cout << comp[i];
        }
        cout << "}";
    }
    cout << endl;
}

int main()
{
    int node_number, edge_number;
    cin >> node_number >> edge_number;
    vector<vector<int>> graph(node_number, vector<int>(node_number, 0));
    for (int i = 0; i < edge_number; i++)
    {
        int node_1, node_2;
        cin >> node_1 >> node_2;
        graph[node_1][node_2] = 1;
        graph[node_2][node_1] = 1;
    }

    // DFS遍历
    vector<bool> visited_dfs(node_number, false);
    vector<vector<int>> dfs_components;

    for (int i = 0; i < node_number; i++)
    {
        if (!visited_dfs[i])
        {
            vector<int> component;
            dfs_component(graph, i, visited_dfs, component);
            dfs_components.push_back(component);
        }
    }

    // BFS遍历
    vector<bool> visited_bfs(node_number, false);
    vector<vector<int>> bfs_components;

    for (int i = 0; i < node_number; i++)
    {
        if (!visited_bfs[i])
        {
            vector<int> component;
            bfs_component(graph, i, visited_bfs, component);
            bfs_components.push_back(component);
        }
    }

    // 输出结果
    print_components(dfs_components);
    print_components(bfs_components);

    return 0;
}