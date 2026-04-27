#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Tree_node
{
    int number = 0;
    int value = 0;
    Tree_node *parent = nullptr;
    Tree_node *l_child = nullptr;
    Tree_node *r_child = nullptr;
};

class Tree
{
public:
    Tree_node *root;
    vector<Tree_node *> Tree_node_list;

    Tree()
    {
        root = nullptr; // 【修复】初始为空，避免占位节点干扰查找与插入
    }

    ~Tree()
    {
        for (auto node : Tree_node_list)
            delete node;
        Tree_node_list.clear();
    }

    // 辅助:安全移除记录,防止析构时重复释放
    void remove_from_list(Tree_node *node)
    {
        auto it = std::find(Tree_node_list.begin(), Tree_node_list.end(), node);
        if (it != Tree_node_list.end())
            Tree_node_list.erase(it);
    }

    Tree_node *find(int num, Tree_node *node_p)
    {
        if (!node_p)
            return nullptr;
        if (num == node_p->value)
            return node_p;
        if (num > node_p->value)
            return find(num, node_p->r_child); // 【修复】补全 return
        return find(num, node_p->l_child);
    }

    int start_find(int num)
    {
        Tree_node *res = find(num, root);
        return res ? res->number : 0; // 【修复】防崩溃，不存在返回0
    }

    int insert(int num, Tree_node *node_p)
    {
        if (num == node_p->value)
        {
            node_p->number++;
            return 0;
        }
        if (num > node_p->value)
        {
            if (!node_p->r_child)
            {
                Tree_node *new_node = new Tree_node;
                new_node->value = num;
                new_node->number = 1;
                new_node->parent = node_p;
                node_p->r_child = new_node;
                Tree_node_list.push_back(new_node);
                return 0;
            }
            return insert(num, node_p->r_child); // 【修复】补全 return
        }
        if (num < node_p->value)
        {
            if (!node_p->l_child)
            {
                Tree_node *new_node = new Tree_node;
                new_node->value = num;
                new_node->number = 1;
                new_node->parent = node_p;
                node_p->l_child = new_node;
                Tree_node_list.push_back(new_node);
                return 0;
            }
            return insert(num, node_p->l_child); // 【修复】补全 return
        }
        return 0;
    }

    int start_insert(int num)
    {
        if (!root)
        { // 【修复】处理空树首次插入
            root = new Tree_node;
            root->value = num;
            root->number = 1;
            Tree_node_list.push_back(root);
            return 0;
        }
        return insert(num, root);
    }

    Tree_node *find_min(Tree_node *start)
    {
        if (!start)
            return nullptr;
        while (start->l_child)
            start = start->l_child; // 【修复】循环至最左端
        return start;
    }

    Tree_node *find_max(Tree_node *start)
    {
        if (!start)
            return nullptr;
        while (start->r_child)
            start = start->r_child;
        return start;
    }

    int delete_node(int num)
    {
        Tree_node *node_p = find(num, root);
        if (!node_p)
        {
            cout << "None" << endl;
            return -1;
        }

        if (node_p->number > 1)
        {
            node_p->number--;
            return 0;
        }

        // 情况1&2：叶子 或 仅有一个子节点
        Tree_node *child = node_p->l_child ? node_p->l_child : node_p->r_child;
        if (!node_p->l_child || !node_p->r_child)
        {
            if (node_p == root)
            {
                root = child;
                if (root)
                    root->parent = nullptr;
            }
            else
            {
                if (node_p->parent->l_child == node_p)
                    node_p->parent->l_child = child;
                else
                    node_p->parent->r_child = child;
                if (child)
                    child->parent = node_p->parent;
            }
            remove_from_list(node_p);
            delete node_p;
            return 0;
        }

        // 情况3：左右子树均存在 → 用右子树最小值（中序后继）替代
        Tree_node *succ = find_min(node_p->r_child);
        node_p->value = succ->value;
        node_p->number = succ->number;

        // 删除后继 succ（succ 必无左孩子，可能有右孩子）
        Tree_node *succ_child = succ->r_child;
        if (succ->parent->l_child == succ)
            succ->parent->l_child = succ_child;
        else
            succ->parent->r_child = succ_child;
        if (succ_child)
            succ_child->parent = succ->parent;

        remove_from_list(succ);
        delete succ;
        return 0;
    }

    int get_min()
    {
        if (!root)
            return 0; // 题目保证非空
        return find_min(root)->value;
    }

    int get_predecessor(int x)
    {
        Tree_node *curr = root;
        int pred_val = 0;
        bool exists = false;
        while (curr)
        {
            if (curr->value < x)
            {
                pred_val = curr->value;
                exists = true;
                curr = curr->r_child; // 尝试找更大但仍小于x的值
            }
            else
            {
                curr = curr->l_child;
            }
        }
        return exists ? pred_val : INT_MIN;
    }
};

int main()
{
    int n;
    if (!(cin >> n))
        return 0;
    Tree bst;
    while (n--)
    {
        int op, x;
        cin >> op;
        if (op == 1)
        {
            cin >> x;
            bst.start_insert(x);
        }
        else if (op == 2)
        {
            cin >> x;
            bst.delete_node(x);
        }
        else if (op == 3)
        {
            cin >> x;
            cout << bst.start_find(x) << endl;
        }
        else if (op == 4)
        {
            cout << bst.get_min() << endl;
        }
        else if (op == 5)
        {
            cin >> x;
            int p = bst.get_predecessor(x);
            if (p == INT_MIN)
                cout << "None" << endl;
            else
                cout << p << endl;
        }
    }
    return 0;
}