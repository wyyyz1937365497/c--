#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> t(n);                     // 每门课程的学时
    vector<vector<int>> prerequisites(n); // 前置课程列表
    vector<vector<int>> adj(n);           // 邻接表：adj[i]表示课程i的后置课程
    vector<int> in_degree(n, 0);          // 入度

    // 读取输入
    for (int i = 0; i < n; i++)
    {
        cin >> t[i];
        int ci;
        cin >> ci;
        for (int j = 0; j < ci; j++)
        {
            int pre;
            cin >> pre;
            pre--; // 转换为0-indexed
            prerequisites[i].push_back(pre);
            adj[pre].push_back(i);
            in_degree[i]++;
        }
    }

    // 拓扑排序计算最早完成时间
    vector<int> earliest(n, 0); // earliest[i]表示课程i最早完成的时间
    queue<int> q;
    vector<int> in_deg_copy = in_degree;

    // 将入度为0的课程加入队列
    for (int i = 0; i < n; i++)
    {
        if (in_deg_copy[i] == 0)
        {
            q.push(i);
            earliest[i] = t[i]; // 没有前置课程，最早完成时间就是自身学时
        }
    }

    vector<int> topo_order; // 拓扑序
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);

        for (int v : adj[u])
        {
            // 更新v的最早开始时间：所有前置课程中最晚完成的
            earliest[v] = max(earliest[v], earliest[u]);
            in_deg_copy[v]--;
            if (in_deg_copy[v] == 0)
            {
                earliest[v] += t[v]; // 加上自身学时
                q.push(v);
            }
        }
    }

    // 计算总的最短毕业时间
    int total_time = 0;
    for (int i = 0; i < n; i++)
    {
        total_time = max(total_time, earliest[i]);
    }

    // 计算最晚完成时间（反向拓扑排序）
    vector<int> latest(n, total_time); // latest[i]表示课程i最晚必须完成的时间

    // 计算出度
    vector<int> out_degree(n, 0);
    for (int i = 0; i < n; i++)
    {
        out_degree[i] = adj[i].size();
    }

    // 反向拓扑排序，使用队列
    queue<int> rq;
    vector<int> out_deg_temp = out_degree;

    for (int i = 0; i < n; i++)
    {
        if (out_deg_temp[i] == 0)
        {
            rq.push(i);
            latest[i] = total_time;
        }
    }

    while (!rq.empty())
    {
        int u = rq.front();
        rq.pop();

        for (int pre : prerequisites[u])
        {
            // pre的最晚完成时间不能超过u的最晚开始时间
            latest[pre] = min(latest[pre], latest[u] - t[u]);
            out_deg_temp[pre]--;
            if (out_deg_temp[pre] == 0)
            {
                rq.push(pre);
            }
        }
    }

    // 输出结果
    for (int i = 0; i < n; i++)
    {
        // 判断是否在关键路径上
        // 如果课程i的最早完成时间 == 最晚完成时间，则在关键路径上
        bool on_critical_path = (earliest[i] == latest[i]);

        cout << earliest[i] << " " << (on_critical_path ? 1 : 0) << endl;
    }

    return 0;
}