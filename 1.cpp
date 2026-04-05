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
int main()
{
    int n = 0;
    if (!(cin >> n))
        return 0;
    cin.get();
    Tree_stack tree_stack(n);

    Tree_node *root = nullptr;
    Tree_node *last_pop = nullptr;
    string input;
    for (int i = 0; i < 2 * n; ++i)
    {
        if (!getline(cin, input))
            break;
        vector<string> command_list = split(input);
        if (command_list[0] == "push")
        {
            char val = command_list[1][0];
            Tree_node *node = new Tree_node();
            node->content = val;
            if (tree_stack.length == 0)
            {
                if (last_pop == nullptr)
                {
                    root = node;
                }
                else
                {
                    last_pop->r_child = node;
                    last_pop = nullptr;
                }
            }
            else
            {
                Tree_node *parent = tree_stack.get_top()->tree_Node;
                if (last_pop != nullptr)
                {
                    last_pop->r_child = node;
                    last_pop = nullptr;
                }
                else
                {
                    parent->l_child = node;
                }
            }
            tree_stack.push(node, 0);
        }
        else if (command_list[0] == "pop")
        {
            stack_node *top = tree_stack.get_top();
            if (top != nullptr)
            {
                last_pop = top->tree_Node;
                tree_stack.pop();
            }
        }
    }
    string result = "";
    post_order(root, result);
    cout << result << endl;
    delete_tree(root);
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