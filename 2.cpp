#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct Tree_node
{
    Tree_node *parent;
    Tree_node *l_child;
    Tree_node *r_child;
    int staute = 0;
};
class Tree
{
public:
    Tree_node *root;
    vector<Tree_node *> Tree_node_list;
    Tree(int n)
    {
        root = new Tree_node;
        root->parent = nullptr;
        Tree_node_list.resize(n, nullptr); // 初始化为 nullptr
        Tree_node_list[0] = root;
    }
    ~Tree()
    {
        for (auto node : Tree_node_list)
        {
            if (node != nullptr)
            {
                delete node;
            }
        }
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, start;
    if (!(cin >> n >> start))
        return 0;
    Tree tree(n);
    for (int i = 0; i < n; i++)
    {
        if (tree.Tree_node_list[i] == nullptr)
        {
            tree.Tree_node_list[i] = new Tree_node;
        }
        Tree_node *current_node_p = tree.Tree_node_list[i];
        int l_child, r_child;
        cin >> l_child >> r_child;
        if (l_child != -1)
        {
            if (tree.Tree_node_list[l_child] == nullptr)
                tree.Tree_node_list[l_child] = new Tree_node;

            Tree_node *l_child_node = tree.Tree_node_list[l_child];
            current_node_p->l_child = l_child_node;
            l_child_node->parent = current_node_p;
        }
        else
        {
            current_node_p->l_child = nullptr;
        }
        if (r_child != -1)
        {
            if (tree.Tree_node_list[r_child] == nullptr)
                tree.Tree_node_list[r_child] = new Tree_node;

            Tree_node *r_child_node = tree.Tree_node_list[r_child];
            current_node_p->r_child = r_child_node;
            r_child_node->parent = current_node_p;
        }
        else
        {
            current_node_p->r_child = nullptr;
        }
    }
    Tree_node *start_node = tree.Tree_node_list[start];
    start_node->staute = 1;
    int infected_count = 1;
    int time = 0;
    queue<Tree_node *> q;
    q.push(start_node);
    while (!q.empty())
    {
        int level_size = q.size();
        bool has_new_infection = false;
        for (int i = 0; i < level_size; i++)
        {
            Tree_node *curr = q.front();
            q.pop();
            Tree_node *neighbors[3] = {curr->l_child, curr->r_child, curr->parent};
            for (int j = 0; j < 3; j++)
            {
                Tree_node *neighbor = neighbors[j];
                if (neighbor != nullptr && neighbor->staute == 0)
                {
                    neighbor->staute = 1;
                    q.push(neighbor);
                    infected_count++;
                    has_new_infection = true;
                }
            }
        }
        if (has_new_infection)
        {
            time++;
        }
    }
    cout << time << endl;
}