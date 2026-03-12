#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;
#define NODESIZE 200
#define INIT_SIZE 10
#define INCREASE_SIZE 10

vector<string> split(const string &str);
struct studentNode
{
    char id[100] = {};
    char name[100] = {};
};

class studentTable
{
public:
    int length = 0;
    int list_length;
    int node_size = NODESIZE;
    studentNode *node_add;
    studentTable()
    {
        node_add = (studentNode *)malloc(sizeof(studentNode) * INIT_SIZE);
        list_length = INIT_SIZE;
    }
    ~studentTable()
    {
        free(node_add);
    }
    int check_name(const char *name)
    {
        studentNode *node_p = node_add;
        for (int i = 0; i < length; i++)
        {
            if (strcmp(node_p->name, name) == 0)
            {
                return i;
            }
            node_p += 1;
        }
        return -1;
    }
    int check_id(const char *id)
    {
        studentNode *node_p = node_add;
        for (int i = 0; i < length; i++)
        {
            if (strcmp(node_p->id, id) == 0)
            {
                return i;
            }
            node_p += 1;
        }
        return -1;
    }
    // 在指定位置插入学生节点，index 为插入位置，id 为学号，name 为姓名
    int inset_node(int index, const char *id, const char *name)
    {
        // 检查索引是否合法，index 小于 0 或大于当前长度则返回 -1 表示插入失败
        if (index < 0 || index > length)
        {
            return -1;
        }

        // 如果当前元素个数等于数组容量，需要扩容
        if (length == list_length)
        {
            // 使用 realloc 重新分配内存，增加 INCREASE_SIZE 个节点空间
            studentNode *new_node_ass = (studentNode *)realloc(node_add, (list_length + INCREASE_SIZE) * sizeof(studentNode));
            // 如果内存重新分配失败，返回 nullptr，插入失败
            if (new_node_ass == nullptr)
            {
                return -1;
            }
            // 将新分配的内存地址赋值给 node_add
            node_add = new_node_ass;
            // 更新数组容量
            list_length += INCREASE_SIZE;
        }

        // 如果在末尾插入（index 等于当前长度）
        if (index == length)
        {
            // 获取要插入位置的指针
            studentNode *node_p = node_add + length;
            // 将学号复制到新节点
            strcpy(node_p->id, id);
            // 将姓名复制到新节点
            strcpy(node_p->name, name);
        }
        else
        {
            // 如果不是在末尾插入，需要将插入位置后的所有元素向后移动一位
            // 从最后一个元素开始向前遍历，直到插入位置的下一个元素
            for (int i = length; i > index; i--)
            {
                // 获取前一个节点的指针
                studentNode *pre_node_p = node_add + i - 1;
                // 获取后一个节点的指针（当前要移动到的位置）
                studentNode *later_node_p = node_add + i;
                // 将前一个节点的学号复制到后一个节点
                strcpy(later_node_p->id, pre_node_p->id);
                // 将前一个节点的姓名复制到后一个节点
                strcpy(later_node_p->name, pre_node_p->name);
            }
            // 获取要插入位置的指针
            studentNode *node_p = node_add + index;
            // 将学号复制到新节点
            strcpy(node_p->id, id);
            // 将姓名复制到新节点
            strcpy(node_p->name, name);
        }
        // 学生表长度加 1
        length += 1;
        // 返回 0 表示插入成功
        return 0;
    }
    int remove_node(int index)
    {
        // 检查索引是否合法，index 小于 0 或大于等于当前长度则返回 -1 表示删除失败
        if (index < 0 || index >= length)
        {
            return -1;
        }
        else
        {
            // 从删除位置开始，将后续所有节点向前移动一位覆盖被删除节点
            for (int i = index; i < length - 1; i++)
            {
                studentNode *pre_node_p = node_add + i;
                studentNode *later_node_p = node_add + i + 1;
                strcpy(pre_node_p->id, later_node_p->id);
                strcpy(pre_node_p->name, later_node_p->name);
            }
            // 学生表长度减 1
            length -= 1;
            return 0;
        }
    }
};

int main()
{
    studentTable stt;
    int num;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        char id[100] = {};
        char name[100] = {};
        cin >> id >> name;
        stt.inset_node(stt.length, id, name);
    }
    cin.ignore();
    string input;
    while (getline(cin, input))
    {
        if (input.empty())
        {
            continue;
        }

        vector<string> command_list = split(input);
        if (command_list.empty())
        {
            continue;
        }
        if (command_list[0] == "end" || command_list[0] == "exit")
        {
            cout << stt.length << endl;
            break;
        }

        if (command_list[0] == "insert")
        {
            if (command_list.size() < 4)
            {
                cout << -1 << endl;
                continue;
            }
            cout << stt.inset_node(stoi(command_list[1]) - 1, command_list[2].c_str(), command_list[3].c_str()) << endl;
        }
        else if (command_list[0] == "remove")
        {
            if (command_list.size() < 2)
            {
                cout << -1 << endl;
                continue;
            }
            cout << stt.remove_node(stoi(command_list[1]) - 1) << endl;
        }
        else if (command_list[0] == "check")
        {
            if (command_list.size() < 3)
            {
                cout << -1 << endl;
                continue;
            }
            if (command_list[1] == "no")
            {
                int index = stt.check_id(command_list[2].c_str());
                if (index < 0)
                {
                    cout << -1 << endl;
                    continue;
                }
                studentNode *node_p = stt.node_add + index;
                cout << index + 1 << " " << node_p->id << " " << node_p->name << endl;
            }
            else
            {
                int index = stt.check_name(command_list[2].c_str());
                if (index < 0)
                {
                    cout << -1 << endl;
                    continue;
                }
                studentNode *node_p = stt.node_add + index;
                cout << index + 1 << " " << node_p->id << " " << node_p->name << endl;
            }
        }
    }
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