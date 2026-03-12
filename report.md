# 作业 HW0*实验报告

姓名：王尹囿 学号：2552304日期：2026年3月12日

## 1.涉及数据结构和相关背景

本周作业用到的都是线性表的知识，线性表是在内存中连续存储的线性结构，只要确定年对应的表的首项的地址就可以直接根据索引跳转到指定项。

## 2.实验内容

### 2.1 轮转数组

#### 2.1.1 问题描述

给定一个整数顺序表nums，将顺序表中的元素向右轮转 k 个位置，其中 k 是非负数。

#### 2.1.2 基本要求

输入第一行两个整数n和k，分别表示nums的元素个数n，和向右轮转k个位置，第二行包括n个整数，为顺序表nums中的元素。输出轮转后的顺序表中的元素。

#### 2.1.3 数据结构设计

```
vector<int> num_list(num_len) //由于第一题面向int的表已有现成实现故直接使用，后续题目使用自定义数据结构
```

#### 2.1.4 功能说明（函数、类）

```

        num_turn = num_turn % num_len; //通过取余操作排除多次循环轮转带来的影响

    for (int i = 0; i < num_len; i++)
    {
        if (i + num_turn < num_len)
        {
            cin >> num_list[i + num_turn];
        }
        else
        {
            cin >> num_list[i + num_turn - num_len];//轮转逻辑，第一次写的时候产生了越界，进而设计年保护，后来发现是轮转数量不对导致的
        }
    }


```

### 2.2 学生信息管理

#### 2.2.1 问题描述

本题 定义一个包含学生信息（学号，姓名）的的 顺序表，使其具有如下功能：(1) 根据指定学生个数，逐个输入学生信息；(2) 给定一个学生信息，插入到表中指定的位置；(3) 删除指定位置的学生记录；(4) 分别根据姓名和学号进行查找，返回此学生的信息；(5) 统计表中学生个数。

#### 2.2.2 基本要求

第1行是学生总数n，接下来n行是对学生信息的描述，每行是一名学生的学号、姓名，用空格分割；(学号、姓名均用字符串表示,字符串长度<100)，接下来是若干行对顺序表的操作：(每行内容之间用空格分隔)
insert i 学号 姓名: 表示在第i个位置插入学生信息, 若i位置不合法，输出-1，否则输出0
remove j:表示删除第j个元素，若元素位置不合适，输出-1，否则输出0
check name 姓名y：查找姓名y在顺序表中是否存在，若存在，输出其位置序号及学号、姓名，若不存在，输出-1。
check no 学号x：查找学号x在顺序表中是否存在，若存在，输出其位置序号及学号、姓名，若不存在，输出-1。
end: 操作结束，输出学生总人数，退出程序。

#### 2.2.3 数据结构设计

```
struct studentNode
{
    char id[100] = {};
    char name[100] = {};
};//保存学生信息的每一项，因为使用了c的方法管理内存，所以没有使用string类
```

#### 2.2.4 功能说明（函数、类）

```
class studentTable
{
public:
    int length = 0;//表中有效项的长度
    int list_length;//线性表的数据存储起始地址
    int node_size = NODESIZE;//线性表的单个数据存储长度
    studentNode *node_add;//线性表的数据存储起始地址
    studentTable()//构造函数，初始化线性表，手动分配内存
    {
        node_add = (studentNode *)malloc(sizeof(studentNode) * INIT_SIZE);
        list_length = INIT_SIZE;
    }
    ~studentTable()//析构函数，释放内存
    {
        free(node_add);
    }
    int check_name(const char *name)//根据姓名查找学生信息
    int check_id(const char *id)//根据学号查找学生信息
    int inset_node(int index, const char *id, const char *name)//在指定位置插入学生信息
    int remove_node(int index)//删除指定位置的学生信息
};
```

```
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
```
```
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

```

### 2.4 扑克牌游戏

#### 2.4.1 问题描述

扑克牌有4种花色：黑桃（Spade）、红心（Heart）、梅花（Club）、方块（Diamond）。每种花色有13张牌，编号从小到大为：A,2,3,4,5,6,7,8,9,10,J,Q,K。

对于一个扑克牌堆，定义以下4种操作命令：
1) 添加（Append）：添加一张扑克牌到牌堆的底部。如命令“Append Club Q”表示添加一张梅花Q到牌堆的底部。
2) 抽取（Extract）：从牌堆中抽取某种花色的所有牌，按照编号从小到大进行排序，并放到牌堆的顶部。如命令“Extract Heart”表示抽取所有红心牌，排序之后放到牌堆的顶部。
3) 反转（Revert）：使整个牌堆逆序。
4) 弹出（Pop）：如果牌堆非空，则除去牌堆顶部的第一张牌，并打印该牌的花色和数字；如果牌堆为空，则打印NULL。
初始时牌堆为空。输入n个操作命令（1 ≤ n ≤200），执行对应指令。所有指令执行完毕后打印牌堆中所有牌花色和数字（从牌堆顶到牌堆底），如果牌堆为空，则打印NULL
注意：每种花色和编号的牌数量不限。
对于20%的数据，n<=20，有Append、Pop指令
对于40%的数据，n<=50，有Append、Pop、Revert指令
对于100%的数据，n<=200，有Append、Pop、Revert、Extract指令
从右上方下载p98.py并运行以生成随机测试数据

#### 2.4.2 基本要求

第一行输入一个整数n，表示命令的数量。
接下来的n行，每一行输入一个命令。
输出若干行，每次收到Pop指令后输出一行（花色和数子或NULL），最后将牌堆中的牌从牌堆顶到牌堆底逐一输出（花色和数字），若牌堆为空则输出NULL

#### 2.4.3 数据结构设计

```
vector<int> num_list(num_len) //由于第一题面向int的表已有现成实现故直接使用，后续题目使用自定义数据结构
```

#### 2.4.4 功能说明（函数、类）

```

        num_turn = num_turn % num_len; //通过取余操作排除多次循环轮转带来的影响

    for (int i = 0; i < num_len; i++)
    {
        if (i + num_turn < num_len)
        {
            cin >> num_list[i + num_turn];
        }
        else
        {
            cin >> num_list[i + num_turn - num_len];//轮转逻辑，第一次写的时候产生了越界，进而设计年保护，后来发现是轮转数量不对导致的
        }
    }


```
