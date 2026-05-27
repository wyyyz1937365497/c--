#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

// Dijkstra算法求单源最短路径
vector<ll> dijkstra(int start, const vector<vector<pair<int, int>>> &graph, int n)
{
    vector<ll> dist(n + 1, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto &edge : graph[u])
        {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    // 建图（无向图）
    vector<vector<pair<int, int>>> graph(N + 1);
    for (int i = 0; i < M; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        graph[x].push_back({y, w});
        graph[y].push_back({x, w});
    }

    int H, R;
    cin >> H >> R;

    // 读取有牧草的点
    vector<int> grass_points(H);
    for (int i = 0; i < H; i++)
    {
        cin >> grass_points[i];
    }

    // 预处理：从每个牧草点运行Dijkstra，计算到所有点的最短距离
    // 为了优化，我们只需要知道每个点到最近牧草点的距离
    // 使用多源Dijkstra：将所有牧草点作为起点

    vector<ll> dist_to_grass(N + 1, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    // 将所有牧草点加入优先队列，距离为0
    for (int grass : grass_points)
    {
        dist_to_grass[grass] = 0;
        pq.push({0, grass});
    }

    // 多源Dijkstra
    while (!pq.empty())
    {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist_to_grass[u])
            continue;

        for (auto &edge : graph[u])
        {
            int v = edge.first;
            int w = edge.second;

            if (dist_to_grass[u] + w < dist_to_grass[v])
            {
                dist_to_grass[v] = dist_to_grass[u] + w;
                pq.push({dist_to_grass[v], v});
            }
        }
    }

    // 处理每匹小马的查询
    for (int i = 0; i < R; i++)
    {
        int start, end;
        cin >> start >> end;

        // 策略：start -> 某个牧草点 -> end
        // 我们需要枚举所有牧草点，找到最小值
        // 但这样是O(R*H)，对于R,H<=1000是可以接受的

        // 更优的方法：
        // 从start运行Dijkstra得到dist_start[]
        // 从end运行Dijkstra得到dist_end[]
        // 答案 = min(dist_start[grass] + dist_end[grass]) for all grass in grass_points

        // 但由于R可能达到1000，每次运行两次Dijkstra可能会超时
        // 更好的方法：预先计算所有点到所有点的距离？不行，空间太大

        // 最优解法：对于每匹小马，运行两次Dijkstra
        vector<ll> dist_from_start = dijkstra(start, graph, N);
        vector<ll> dist_from_end = dijkstra(end, graph, N);

        ll ans = INF;
        for (int grass : grass_points)
        {
            if (dist_from_start[grass] < INF && dist_from_end[grass] < INF)
            {
                ans = min(ans, dist_from_start[grass] + dist_from_end[grass]);
            }
        }

        cout << ans << "\n";
    }

    return 0;
}