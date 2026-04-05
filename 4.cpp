#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Tree_node
{
    Tree_node *l_child = nullptr;
    Tree_node *r_child = nullptr;
    char icon = '\0';
};

class Tree
{
public:
    vector<Tree_node *> Tree_node_list;
    int root = -1;

    Tree(int n)
    {
        if (n > 0)
        {
            Tree_node_list.resize(n);
            for (int i = 0; i < n; i++)
            {
                Tree_node_list[i] = new Tree_node;
            }
        }
    }
    ~Tree()
    {
        for (auto x : Tree_node_list)
        {
            delete x;
        }
    }
    int calcDepth(Tree_node *node)
    {
        if (node == nullptr)
            return 0;
        return 1 + max(calcDepth(node->l_child), calcDepth(node->r_child));
    }

    int get_tree_depth()
    {
        if (root == -1 || Tree_node_list.empty())
            return 0;
        return calcDepth(Tree_node_list[root]);
    }
};
bool isIsomorphic(Tree_node *t1, Tree_node *t2)
{
    if (t1 == nullptr && t2 == nullptr)
        return true;
    if (t1 == nullptr || t2 == nullptr)
        return false;
    if (t1->icon != t2->icon)
        return false;
    return (isIsomorphic(t1->l_child, t2->l_child) && isIsomorphic(t1->r_child, t2->r_child)) ||
           (isIsomorphic(t1->l_child, t2->r_child) && isIsomorphic(t1->r_child, t2->l_child));
}
int char2index(const string &s)
{
    if (s == "-")
        return -1;
    return stoi(s);
}

int main()
{
    int n1 = 0;
    if (!(cin >> n1))
        return 0;

    Tree tree1(n1);
    vector<bool> is_child1(n1, false);

    for (int i = 0; i < n1; i++)
    {
        char icon;
        string l_str, r_str;
        cin >> icon >> l_str >> r_str;
        int l_idx = char2index(l_str);
        int r_idx = char2index(r_str);

        tree1.Tree_node_list[i]->icon = icon;
        if (l_idx != -1)
        {
            tree1.Tree_node_list[i]->l_child = tree1.Tree_node_list[l_idx];
            is_child1[l_idx] = true;
        }
        if (r_idx != -1)
        {
            tree1.Tree_node_list[i]->r_child = tree1.Tree_node_list[r_idx];
            is_child1[r_idx] = true;
        }
    }
    int root1 = -1;
    for (int i = 0; i < n1; i++)
    {
        if (!is_child1[i])
        {
            root1 = i;
            break;
        }
    }
    tree1.root = root1;

    int n2 = 0;
    cin >> n2;
    Tree tree2(n2);
    vector<bool> is_child2(n2, false);

    for (int i = 0; i < n2; i++)
    {
        char icon;
        string l_str, r_str;
        cin >> icon >> l_str >> r_str;
        int l_idx = char2index(l_str);
        int r_idx = char2index(r_str);

        tree2.Tree_node_list[i]->icon = icon;
        if (l_idx != -1)
        {
            tree2.Tree_node_list[i]->l_child = tree2.Tree_node_list[l_idx];
            is_child2[l_idx] = true;
        }
        if (r_idx != -1)
        {
            tree2.Tree_node_list[i]->r_child = tree2.Tree_node_list[r_idx];
            is_child2[r_idx] = true;
        }
    }
    int root2 = -1;
    for (int i = 0; i < n2; i++)
    {
        if (!is_child2[i])
        {
            root2 = i;
            break;
        }
    }
    tree2.root = root2;

    bool is_same = false;
    if (n1 == n2)
    {
        Tree_node *r1 = (root1 != -1) ? tree1.Tree_node_list[root1] : nullptr;
        Tree_node *r2 = (root2 != -1) ? tree2.Tree_node_list[root2] : nullptr;
        is_same = isIsomorphic(r1, r2);
    }
    cout << (is_same ? "Yes" : "No") << endl;
    cout << tree1.get_tree_depth() << endl;
    cout << tree2.get_tree_depth() << endl;
}