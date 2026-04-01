#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
using namespace std;
vector<string> split(const string &str);
struct Tree_node
{
    char content;
    Tree_node *l_child = nullptr;
    Tree_node *r_child = nullptr;
};
struct stack_node
{
    Tree_node *tree_Node;
    int staute;
};
class Tree_stack
{
public:
    int length = 0;
    int stack_length = 0;
    stack_node *stack_base;
    stack_node *stack_head;

    Tree_stack(int list_length)
    {
        stack_base = (stack_node *)malloc(list_length * sizeof(stack_node));
        stack_length = list_length;
        stack_head = stack_base;
    }
    ~Tree_stack()
    {
        free(stack_base);
    }
    int push(Tree_node *tree_node, int staute)
    {
        if (stack_length - length == 0)
        {
            return -1;
        }
        stack_head->tree_Node = tree_node;
        stack_head->staute = staute;
        stack_head += 1;
        length += 1;
        return 0;
    }
    int pop()
    {
        if (length == 0)
        {
            return -1;
        }
        stack_head -= 1;
        length -= 1;
        return 0;
    }
    stack_node *get_top()
    {
        if (length == 0)
            return nullptr;
        return stack_head - 1;
    }
};
void post_order(Tree_node *node, string &result);
void delete_tree(Tree_node *node);
/**
 * 主函数，处理输入并构建二叉树，最后输出后序遍历结果
 * @return 程序执行状态
 */
int main()
{
    int n = 0;       // 记录操作序列的长度
    if (!(cin >> n)) // 读取操作序列长度，如果读取失败则退出程序
        return 0;
    cin.get();                // 消耗换行符
    Tree_stack tree_stack(n); // 创建一个大小为n的栈

    Tree_node *root = nullptr;      // 根节点指针
    Tree_node *last_pop = nullptr;  // 记录最近弹出的节点
    string input;                   // 存储输入的命令行
    for (int i = 0; i < 2 * n; ++i) // 执行2n次操作（每个节点需要一次push和一次pop）
    {
        if (!getline(cin, input)) // 读取一行输入
            break;
        vector<string> command_list = split(input); // 分割命令行
        // 处理push命令
        if (command_list[0] == "push")
        {
            char val = (command_list[1])[0];   // 获取要插入的节点值
            Tree_node *node = new Tree_node(); // 创建新节点
            node->content = val;               // 设置节点值
            // 处理根节点情况
            if (tree_stack.length == 0)
            {
                if (last_pop == nullptr) // 栈为空且没有最近弹出的节点，则为根节点
                {
                    root = node;
                }
                else // 栈为空但有最近弹出的节点，则作为右孩子
                {
                    last_pop->r_child = node;
                    last_pop = nullptr;
                }
            }
            else // 栈不为空的情况
            {
                Tree_node *parent = tree_stack.get_top()->tree_Node; // 获取栈顶节点的父节点
                if (last_pop != nullptr)                             // 有最近弹出的节点，则作为右孩子
                {
                    last_pop->r_child = node;
                    last_pop = nullptr;
                }
                else // 没有最近弹出的节点，则作为左孩子
                {
                    parent->l_child = node;
                }
            }
            tree_stack.push(node, 0); // 将新节点压入栈
        }
        // 处理pop命令
        else if (command_list[0] == "pop")
        {
            stack_node *top = tree_stack.get_top(); // 获取栈顶元素
            if (top != nullptr)
            {
                last_pop = top->tree_Node; // 记录最近弹出的节点
                tree_stack.pop();          // 弹出栈顶元素
            }
        }
    }
    string result = "";       // 存储后序遍历结果
    post_order(root, result); // 执行后序遍历
    cout << result << endl;   // 输出结果
    delete_tree(root);        // 释放树内存
}
void post_order(Tree_node *node, string &result)
{
    if (node == nullptr)
        return;
    post_order(node->l_child, result);
    post_order(node->r_child, result);
    result += node->content;
}
void delete_tree(Tree_node *node)
{
    if (node == nullptr)
        return;
    delete_tree(node->l_child);
    delete_tree(node->r_child);
    delete node;
}
vector<string> split(const string &str)
{
    vector<string> result;
    istringstream iss(str);
    string word;
    while (iss >> word)
    {
        result.push_back(word);
    }
    return result;
}