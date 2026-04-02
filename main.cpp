#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
using namespace std;

// 文件工具类
// 读取 txt 文件内容为 string
static string readTxtFile(const string &filename);
static void writeStringToFile(const string &content, const string &filename);
struct Tree_node
{
    Tree_node *l_child = nullptr;
    Tree_node *r_child = nullptr;
    char content = '\0';
    int percent = 0;
};
class Tree
{
public:
    vector<Tree_node *> Tree_node_list;
    int percent_list[256] = {};
    ~Tree()
    {
        if (!Tree_node_list.empty())
        {
            deleteTree(Tree_node_list[0]);
        }
        Tree_node_list.clear();
    }

    // 递归删除树的辅助函数
    void deleteTree(Tree_node *node)
    {
        if (node == nullptr)
        {
            return;
        }
        deleteTree(node->l_child);
        deleteTree(node->r_child);
        delete node;
    }
    int get_min()
    {
        if (Tree_node_list.empty())
        {
            return -1;
        }
        auto min_it = min_element(Tree_node_list.begin(), Tree_node_list.end(),
                                  [](Tree_node *a, Tree_node *b)
                                  {
                                      return a->percent < b->percent;
                                  });
        return distance(Tree_node_list.begin(), min_it);
    }
};
void generateCodes(Tree_node *node, string code, vector<string> &codes)
{
    if (!node)
        return;
    if (node->l_child == nullptr && node->r_child == nullptr)
    {
        codes[(unsigned char)node->content] = code;
        return;
    }
    generateCodes(node->l_child, code + "0", codes);
    generateCodes(node->r_child, code + "1", codes);
}

int main()
{
    Tree tree;
    string content;
    cout << "请输入文件路径" << endl;
    try
    {
        // 读取 txt 文件到 string
        content = readTxtFile("input.txt");
    }
    catch (const exception &e)
    {
        cerr << "错误：" << e.what() << endl;
        return 1;
    }
    for (unsigned char x : content)
    {
        tree.percent_list[x]++;
    }
    for (int i = 0; i < 256; i++)
    {
        if (tree.percent_list[i] != 0)
        {
            Tree_node *node_p = new Tree_node;
            node_p->content = (char)i;
            node_p->percent = tree.percent_list[i];
            tree.Tree_node_list.push_back(node_p);
        }
    }
    cout << "初始节点数量：" << tree.Tree_node_list.size() << endl;
    while (tree.Tree_node_list.size() > 1)
    {
        int min1_idx = tree.get_min();
        if (min1_idx == -1)
        {
            cerr << "错误：无法获取最小节点" << endl;
            break;
        }
        Tree_node *min1 = tree.Tree_node_list[min1_idx];
        tree.Tree_node_list.erase(tree.Tree_node_list.begin() + min1_idx);
        int min2_idx = tree.get_min();
        if (min2_idx == -1)
        {
            cerr << "错误：无法获取第二个最小节点" << endl;
            delete min1;
            break;
        }
        Tree_node *min2 = tree.Tree_node_list[min2_idx];
        tree.Tree_node_list.erase(tree.Tree_node_list.begin() + min2_idx);
        Tree_node *parent = new Tree_node;
        parent->l_child = min1;
        parent->r_child = min2;
        parent->percent = min1->percent + min2->percent;
        parent->content = '\0';
        tree.Tree_node_list.push_back(parent);
        cout << "合并节点，新节点权值：" << parent->percent
             << ", 剩余节点数：" << tree.Tree_node_list.size() << endl;
    }
    Tree_node *root = nullptr;
    if (!tree.Tree_node_list.empty())
    {
        root = tree.Tree_node_list[0];
        cout << "\n✅ 哈夫曼树构建完成！" << endl;
        cout << "根节点权值：" << root->percent << endl;
        vector<string> codes(256, "");
        generateCodes(root, "", codes);
        cout << "\n部分字符的哈夫曼编码：" << endl;
        int count = 0;
        for (int i = 0; i < 256 && count < 10; i++)
        {
            if (!codes[i].empty())
            {
                char c = (char)i;
                if (c >= 32 && c <= 126)
                {
                    cout << "'" << c << "': " << codes[i] << endl;
                }
                else
                {
                    cout << "ASCII(" << i << "): " << codes[i] << endl;
                }
                count++;
            }
        }
    }
    else
    {
        cerr << "错误：未能构建哈夫曼树" << endl;
        return 1;
    }
    cout << "\n按回车键退出..." << endl;
    cin.get();
    return 0;
}

static string readTxtFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("无法打开文件：" + filename);
    }

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

// 将 string 保存到指定文件名的 txt 文件
static void writeStringToFile(const string &content, const string &filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("无法创建文件：" + filename);
    }

    file << content;
    file.close();
}