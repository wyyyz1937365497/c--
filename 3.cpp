#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>

using namespace std;

struct People_node
{
    string name;
    People_node *parent = nullptr;
    map<string, People_node *> children_list;
};

class Family
{
public:
    People_node *root;
    map<string, People_node *> people_node_list;

    Family(string name)
    {
        root = new People_node;
        root->name = name;
        people_node_list.emplace(name, root);
    }

    ~Family()
    {
        for (const auto &pair : people_node_list)
        {
            delete pair.second;
        }
    }

    // 修复：改为 void，避免无返回值警告
    void add_child(string parent_name, string child_name)
    {
        auto it = people_node_list.find(parent_name);
        if (it == people_node_list.end())
            return;
        People_node *parent_node = it->second;
        People_node *child_node = new People_node;
        child_node->name = child_name;
        child_node->parent = parent_node;
        parent_node->children_list.emplace(child_name, child_node);
        people_node_list.emplace(child_name, child_node);
    }

    bool is_child(string child_name, string parent_name)
    {
        auto it = people_node_list.find(child_name);
        if (it == people_node_list.end())
            return false;
        return it->second->parent != nullptr && it->second->parent->name == parent_name;
    }

    bool is_parent(string parent_name, string child_name)
    {
        return is_child(child_name, parent_name);
    }

    bool is_sibling(string name1, string name2)
    {
        auto it1 = people_node_list.find(name1);
        auto it2 = people_node_list.find(name2);
        if (it1 == people_node_list.end() || it2 == people_node_list.end())
            return false;
        return it1->second->parent == it2->second->parent;
    }

    bool is_ancestor(string anc_name, string desc_name)
    {
        if (anc_name == desc_name)
            return true;
        auto it = people_node_list.find(desc_name);
        if (it == people_node_list.end())
            return false;
        People_node *curr = it->second;
        while (curr->parent != nullptr)
        {
            curr = curr->parent;
            if (curr->name == anc_name)
                return true;
        }
        return false;
    }

    bool is_descendant(string desc_name, string anc_name)
    {
        return is_ancestor(anc_name, desc_name);
    }
};

int count_leading_spaces(const string &str)
{
    int count = 0;
    for (char c : str)
    {
        if (c == ' ')
            count++;
        else
            break;
    }
    return count;
}

int main()
{
    int n, m;
    while (cin >> n >> m && (n != 0 || m != 0))
    {
        string dummy;
        getline(cin, dummy);

        Family *family = nullptr;
        vector<string> parent_stack;
        for (int i = 0; i < n; ++i)
        {
            string line;
            getline(cin, line);
            int spaces = count_leading_spaces(line);
            string name = line.substr(spaces);

            if (family == nullptr)
            {
                // 第一行必为根节点（spaces == 0）
                family = new Family(name);
                parent_stack.clear();
                parent_stack.resize(1);
                parent_stack[0] = name;
            }
            else
            {
                // spaces 即为当前节点深度（0缩进=0层，1空格=1层...）
                if ((int)parent_stack.size() <= spaces)
                    parent_stack.resize(spaces + 1);
                string parent_name = parent_stack[spaces - 1];
                family->add_child(parent_name, name);
                parent_stack[spaces] = name; // 更新该层级的最新节点，供后续同层/子层使用
            }
        }

        // 2. 处理查询语句
        for (int i = 0; i < m; ++i)
        {
            string u, w1, w2, rel, w4, v_dot;
            cin >> u >> w1 >> w2 >> rel >> w4 >> v_dot;
            string v = v_dot;
            if (!v.empty() && v.back() == '.')
                v.pop_back(); // 去除末尾句号

            bool result = false;
            if (rel == "child")
                result = family->is_child(u, v);
            else if (rel == "parent")
                result = family->is_parent(u, v);
            else if (rel == "sibling")
                result = family->is_sibling(u, v);
            else if (rel == "descendant")
                result = family->is_descendant(u, v);
            else if (rel == "ancestor")
                result = family->is_ancestor(u, v);

            cout << (result ? "True" : "False") << endl;
        }

        // 3. 每个测试用例后输出空行
        cout << endl;
        delete family;
    }
    return 0;
}