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
    int append(const char *number, const char *type)
    {
        if (length >= list_length)
        {
            return -1;
        }
        card *node_p = get_item(length);
        strcpy(node_p->number, number);
        strcpy(node_p->type, type);
        length += 1;
        return 0;
    }
    int remove(int index)
    {
        if (index >= length)
        {
            return -1;
        }
        for (; index < length - 1; index++)
        {
            strcpy(get_item(index)->number, get_item(index + 1)->number);
            strcpy(get_item(index)->type, get_item(index + 1)->type);
        }
        length -= 1;
        return 0;
    }
    int insert(int index, const char *number, const char *type)
    {
        if (index < 0 || index > length || length >= list_length)
        {
            return -1;
        }
        for (int q = length; q > index; q--)
        {
            card *pre_node_p = get_item(q - 1);
            card *later_node_p = get_item(q);
            strcpy(later_node_p->number, pre_node_p->number);
            strcpy(later_node_p->type, pre_node_p->type);
        }
        card *node_p = get_item(index);
        strcpy(node_p->number, number);
        strcpy(node_p->type, type);
        length += 1;
        return 0;
    }
    int pop()
    {
        if (length == 0)
        {
            cout << "NULL" << endl;
            return -1;
        }
        card *pre_node_p = node_add;
        card *later_mode_p = node_add;
        cout << pre_node_p->number << " " << pre_node_p->type << endl;
        for (int i = 0; i < length - 1; i++)
        {
            pre_node_p = get_item(i);
            later_mode_p = get_item(i + 1);
            strcpy(pre_node_p->number, later_mode_p->number);
            strcpy(pre_node_p->type, later_mode_p->type);
        }
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
    int extract(const char *suit)
    {
        if (length == 0)
        {
            return 0;
        }
        cards swap(length);
        for (int i = 0; i < length; i++)
        {
            card *node_p = get_item(i);
            if (strcmp(node_p->number, suit) == 0)
            {
                swap.append(node_p->number, node_p->type);
                remove(i);
                i -= 1;
            }
        }
        swap.sort();
        for (int i = 0; i < swap.length; i++)
        {
            this->insert(i, swap.get_item(i)->number, swap.get_item(i)->type);
        }
        return 0;
    }
    int revert()
    {
        if (length == 0)
        {
            return 0;
        }
        cards swap(length);
        for (int i = 0; i < length; i++)
        {
            card *this_node = get_item(i);
            card *swap_node = swap.get_item(length - 1 - i);
            strcpy(swap_node->type, this_node->type);
            strcpy(swap_node->number, this_node->number);
        }
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