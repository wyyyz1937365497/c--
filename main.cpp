#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;
struct card
{
    char number[8] = {};
    char type[3] = {};
};
int turn_card_numer2int(const char *a);
vector<string> split(const string &str);
class cards
{
public:
    card *node_add;
    int length = 0;
    int list_length = 0;
    cards(int steps)
    {
        node_add = (card *)malloc(steps * sizeof(card));
        list_length = steps;
    }
    ~cards()
    {
        free(node_add);
    }
    card *get_item(int index)
    {
        card *node_p = node_add + index;
        return node_p;
    }
    /**
     * 向卡片列表中添加一张新卡片
     *
     * @param number 卡片的编号字符串，将被复制到新卡片节点
     * @param type 卡片的类型字符串，将被复制到新卡片节点
     * @return 成功时返回 0；如果列表已满无法添加则返回 -1
     */
    int append(const char *number, const char *type)
    {
        // 检查列表是否已满，无法添加新元素
        if (length >= list_length)
        {
            return -1;
        }
        // 获取当前末尾位置的卡片节点指针
        card *node_p = get_item(length);
        // 将传入的编号和类型复制到卡片节点中
        strcpy(node_p->number, number);
        strcpy(node_p->type, type);
        // 增加列表长度计数
        length += 1;
        return 0;
    }
    /**
     * 从卡片列表中删除指定位置的卡片
     *
     * @param index 要删除的卡片在列表中的索引位置
     * @return 成功删除时返回 0；如果索引超出范围则返回 -1
     */
    int remove(int index)
    {
        // 检查索引是否超出有效范围
        if (index >= length)
        {
            return -1;
        }
        // 将删除位置后的所有卡片向前移动一位，覆盖被删除的卡片
        for (; index < length - 1; index++)
        {
            strcpy(get_item(index)->number, get_item(index + 1)->number);
            strcpy(get_item(index)->type, get_item(index + 1)->type);
        }
        // 更新列表长度
        length -= 1;
        return 0;
    }
    /**
     * 向卡片列表的指定位置插入一张新卡片
     *
     * @param index 要插入的位置索引，范围为 0 到 length（包含两端）
     * @param number 卡片的编号字符串，将被复制到指定位置的卡片节点
     * @param type 卡片的类型字符串，将被复制到指定位置的卡片节点
     * @return 成功插入时返回 0；如果索引超出范围或列表已满无法插入则返回 -1
     */
    int insert(int index, const char *number, const char *type)
    {
        // 检查索引是否有效以及列表是否已满
        if (index < 0 || index > length || length >= list_length)
        {
            return -1;
        }
        // 将插入位置后的所有卡片向后移动一位，为新卡片腾出空间
        for (int q = length; q > index; q--)
        {
            card *pre_node_p = get_item(q - 1);
            card *later_node_p = get_item(q);
            strcpy(later_node_p->number, pre_node_p->number);
            strcpy(later_node_p->type, pre_node_p->type);
        }
        // 将新卡片数据复制到指定位置
        card *node_p = get_item(index);
        strcpy(node_p->number, number);
        strcpy(node_p->type, type);
        // 更新列表长度
        length += 1;
        return 0;
    }
    /**
     * 从卡片列表中弹出（移除）最后一张卡片
     *
     * 将列表中所有卡片向前移动一位，覆盖第一张卡片，从而实现移除最后一张卡片的效果
     * 如果列表为空则输出"NULL"提示
     *
     * @return 成功时返回 0；如果列表为空无法弹出则返回 -1
     */
    int pop()
    {
        // 检查列表是否为空，无法执行弹出操作
        if (length == 0)
        {
            cout << "NULL" << endl;
            return -1;
        }
        card *pre_node_p = node_add;
        card *later_mode_p = node_add;
        cout << pre_node_p->number << " " << pre_node_p->type << endl;
        // 遍历列表，将后一张卡片的数据复制到前一张卡片位置，实现整体前移
        for (int i = 0; i < length - 1; i++)
        {
            pre_node_p = get_item(i);
            later_mode_p = get_item(i + 1);
            strcpy(pre_node_p->number, later_mode_p->number);
            strcpy(pre_node_p->type, later_mode_p->type);
        }
        // 更新列表长度，完成弹出操作
        length -= 1;
        return 0;
    }
    int sort()
    {
        for (int i = 0; i < length - 1; ++i)
        {
            bool swapped = false;
            for (int j = 0; j < length - i - 1; ++j)
            {
                if (turn_card_numer2int(get_item(j)->type) > turn_card_numer2int(get_item(j + 1)->type))
                {
                    card tmp = *get_item(j);
                    *get_item(j) = *get_item(j + 1);
                    *get_item(j + 1) = tmp;
                    swapped = true;
                }
            }
            if (!swapped)
            {
                break;
            }
        }
        return 0;
    }
    /**
     * 从卡片列表中提取指定编号的卡片，排序后重新插入到列表前端
     *
     * 遍历当前卡片列表，将所有编号与给定参数匹配的卡片移除并暂存到临时列表中，
     * 然后将这些卡片按排序后的顺序重新插入到原列表的起始位置。
     * 此操作会改变原卡片列表的结构和顺序。
     *
     * @param suit 要提取的卡片编号字符串，函数将匹配此编号的所有卡片
     * @return 始终返回 0；如果列表为空则直接返回 0 不执行任何操作
     */
    int extract(const char *suit)
    {
        // 检查列表是否为空，空列表无需执行提取操作
        if (length == 0)
        {
            return 0;
        }
        // 创建临时卡片列表用于存储匹配指定编号的卡片
        cards swap(length);
        // 遍历当前列表，查找并移除所有编号匹配的卡片
        for (int i = 0; i < length; i++)
        {
            card *node_p = get_item(i);
            // 判断当前卡片的编号是否与目标编号匹配
            if (strcmp(node_p->number, suit) == 0)
            {
                // 将匹配的卡片添加到临时列表中
                swap.append(node_p->number, node_p->type);
                // 从原列表中移除该卡片
                remove(i);
                // 调整索引以补偿列表长度减少，确保下次循环访问正确的位置
                i -= 1;
            }
        }
        // 对临时列表中的卡片进行排序
        swap.sort();
        // 将排序后的卡片依次插入回原列表的前端位置
        for (int i = 0; i < swap.length; i++)
        {
            this->insert(i, swap.get_item(i)->number, swap.get_item(i)->type);
        }
        return 0;
    }
    /**
     * 反转卡片列表的顺序
     * 
     * 将当前卡片列表中的所有卡片顺序完全颠倒。通过创建临时交换对象，
     * 先将原列表的卡片倒序复制到交换对象中，再从交换对象复制回原列表。
     *
     * @return 成功时返回 0；如果列表为空也返回 0
     */
    int revert()
    {
        // 空列表无需反转，直接返回
        if (length == 0)
        {
            return 0;
        }
        // 创建临时交换对象用于存储倒序的卡片
        cards swap(length);
        // 第一阶段：将原列表的卡片倒序复制到交换对象中
        for (int i = 0; i < length; i++)
        {
            card *this_node = get_item(i);
            card *swap_node = swap.get_item(length - 1 - i);
            strcpy(swap_node->type, this_node->type);
            strcpy(swap_node->number, this_node->number);
        }
        // 第二阶段：将交换对象的卡片复制回原列表，完成反转
        for (int i = 0; i < length; i++)
        {
            card *this_node = get_item(i);
            card *swap_node = swap.get_item(i);
            strcpy(this_node->type, swap_node->type);
            strcpy(this_node->number, swap_node->number);
        }
        return 0;
    }
};

int main()
{
    int step_number = 0;
    cin >> step_number;
    cin.ignore();
    cards cards_stt(step_number);
    for (int i = 1; i <= step_number; i++)
    {
        string input;
        getline(cin, input);
        if (input.empty())
        {
            i -= 1;
            continue;
        }
        vector<string> command_list = split(input);
        if (command_list[0] == "Append")
        {
            cards_stt.append(command_list[1].c_str(), command_list[2].c_str());
        }
        else if (command_list[0] == "Pop")
        {
            cards_stt.pop();
        }
        else if (command_list[0] == "Extract")
        {
            cards_stt.extract(command_list[1].c_str());
        }
        else if (command_list[0] == "Revert")
        {
            cards_stt.revert();
        }
    }
    if (cards_stt.length == 0)
    {
        cout << "NULL" << endl;
    }
    for (int i = 0; i < cards_stt.length; i++)
    {
        card *node_p = cards_stt.get_item(i);
        cout << node_p->number << " " << node_p->type << endl;
    }
}
int turn_card_numer2int(const char *a)
{
    if (strcmp(a, "A") == 0)
    {
        return 0;
    }
    if (strcmp(a, "2") == 0)
    {
        return 1;
    }
    if (strcmp(a, "3") == 0)
    {
        return 2;
    }
    if (strcmp(a, "4") == 0)
    {
        return 3;
    }
    if (strcmp(a, "5") == 0)
    {
        return 4;
    }
    if (strcmp(a, "6") == 0)
    {
        return 5;
    }
    if (strcmp(a, "7") == 0)
    {
        return 6;
    }
    if (strcmp(a, "8") == 0)
    {
        return 7;
    }
    if (strcmp(a, "9") == 0)
    {
        return 8;
    }
    if (strcmp(a, "10") == 0)
    {
        return 9;
    }
    if (strcmp(a, "J") == 0)
    {
        return 10;
    }
    if (strcmp(a, "Q") == 0)
    {
        return 11;
    }
    if (strcmp(a, "K") == 0)
    {
        return 12;
    }
    return -1;
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