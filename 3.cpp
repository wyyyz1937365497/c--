#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <iomanip>
using namespace std;

// ==================== 数据结构定义 ====================

// 哈夫曼树节点结构
struct Tree_node
{
    Tree_node *l_child = nullptr; // 左孩子指针
    Tree_node *r_child = nullptr; // 右孩子指针
    char content = '\0';          // 节点表示的字符（叶节点有效）
    int percent = 0;              // 权值（频率）
};

// 哈夫曼树类
class Tree
{
public:
    vector<Tree_node *> Tree_node_list; // 节点列表
    int percent_list[256] = {};         // 统计每个字符的频率

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

    // 获取最小权值节点的索引
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

// ==================== 工具函数声明 ====================

static string readTxtFile(const string &filename);
static void writeStringToFile(const string &content, const string &filename);
void generateCodes(Tree_node *node, string code, vector<string> &codes);
string compressFile(const string &content, Tree_node *root, const vector<string> &codes);
string decompressFile(const string &compressed, Tree_node *root);
void writeCompressedFile(const string &compressed, const string &filename);
string readCompressedFile(const string &filename);
void displayHuffmanCodes(const vector<string> &codes);
void showMenu();

// ==================== 哈夫曼编码相关函数 ====================

// 生成哈夫曼编码（递归）
void generateCodes(Tree_node *node, string code, vector<string> &codes)
{
    if (!node)
        return;

    // 叶节点：记录编码
    if (node->l_child == nullptr && node->r_child == nullptr)
    {
        codes[(unsigned char)node->content] = code;
        return;
    }

    // 递归遍历左右子树
    generateCodes(node->l_child, code + "0", codes);
    generateCodes(node->r_child, code + "1", codes);
}

// 使用哈夫曼编码压缩文件
string compressFile(const string &content, Tree_node *root, const vector<string> &codes)
{
    string compressed = "";
    for (char c : content)
    {
        compressed += codes[(unsigned char)c];
    }
    return compressed;
}

// 使用哈夫曼树解码二进制字符串
string decompressFile(const string &compressed, Tree_node *root)
{
    string result = "";
    Tree_node *current = root;

    for (char bit : compressed)
    {
        if (bit == '0')
        {
            current = current->l_child;
        }
        else if (bit == '1')
        {
            current = current->r_child;
        }

        // 到达叶节点，记录字符并回到根节点
        if (current->l_child == nullptr && current->r_child == nullptr)
        {
            result += current->content;
            current = root;
        }
    }

    return result;
}

// ==================== 文件操作函数 ====================

// 读取 txt 文件到 string
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

// 将二进制字符串保存为文件
void writeCompressedFile(const string &compressed, const string &filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("无法创建压缩文件：" + filename);
    }
    file << compressed;
    file.close();
}

// 读取压缩文件
string readCompressedFile(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw runtime_error("无法打开压缩文件：" + filename);
    }

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

// ==================== 显示函数 ====================

// 显示哈夫曼编码表
void displayHuffmanCodes(const vector<string> &codes)
{
    cout << "\n========== 哈夫曼编码表 ==========" << endl;
    int count = 0;
    for (int i = 0; i < 256; i++)
    {
        if (!codes[i].empty())
        {
            char c = (char)i;
            if (c >= 32 && c <= 126)
            {
                cout << "'" << c << "' -> " << setw(20) << codes[i] << "    ";
            }
            else
            {
                cout << "ASCII(" << setw(3) << i << ") -> " << setw(20) << codes[i] << "    ";
            }
            count++;
            if (count % 4 == 0)
                cout << endl;
        }
    }
    cout << endl;
}

// 显示菜单
void showMenu()
{
    cout << "\n========================================" << endl;
    cout << "     哈夫曼编码与译码系统" << endl;
    cout << "========================================" << endl;
    cout << "  1. 压缩文件 (编码)" << endl;
    cout << "  2. 解压文件 (译码)" << endl;
    cout << "  3. 显示哈夫曼编码表" << endl;
    cout << "  4. 退出程序" << endl;
    cout << "========================================" << endl;
    cout << "请选择操作 (1-4): ";
}

// ==================== 主函数 ====================

int main()
{
    Tree tree;
    string content;
    string inputFilename, compressedFilename, decompressedFilename;

    cout << "========================================" << endl;
    cout << "     欢迎使用哈夫曼编码与译码系统" << endl;
    cout << "========================================" << endl;

    // 获取输入文件路径
    cout << "\n请输入待处理的文本文件路径 (默认：input.txt): ";
    getline(cin, inputFilename);
    if (inputFilename.empty())
    {
        inputFilename = "input.txt";
    }

    try
    {
        // 读取 txt 文件到 string
        content = readTxtFile(inputFilename);
        cout << "✓ 成功读取文件：" << inputFilename << endl;
        cout << "  文件大小：" << content.length() << " 字节" << endl;
    }
    catch (const exception &e)
    {
        cerr << "错误：" << e.what() << endl;
        cout << "\n按回车键退出..." << endl;
        cin.get();
        return 1;
    }

    // 统计字符频率
    for (unsigned char x : content)
    {
        tree.percent_list[x]++;
    }

    // 创建初始节点
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

    cout << "\n统计信息：" << endl;
    cout << "  不同字符数量：" << tree.Tree_node_list.size() << endl;

    // 构建哈夫曼树
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

        // 创建父节点
        Tree_node *parent = new Tree_node;
        parent->l_child = min1;
        parent->r_child = min2;
        parent->percent = min1->percent + min2->percent;
        parent->content = '\0';
        tree.Tree_node_list.push_back(parent);
    }

    // 获取根节点
    Tree_node *root = nullptr;
    if (!tree.Tree_node_list.empty())
    {
        root = tree.Tree_node_list[0];
        cout << "\n✅ 哈夫曼树构建完成！" << endl;
        cout << "  根节点权值：" << root->percent << endl;
    }
    else
    {
        cerr << "错误：未能构建哈夫曼树" << endl;
        cout << "\n按回车键退出..." << endl;
        cin.get();
        return 1;
    }

    // 生成哈夫曼编码
    vector<string> codes(256, "");
    generateCodes(root, "", codes);

    // 主菜单循环
    int choice;
    do
    {
        showMenu();
        cin >> choice;
        cin.ignore(); // 清除换行符

        switch (choice)
        {
        case 1: // 压缩文件
        {
            cout << "\n【文件压缩】" << endl;

            // 压缩文件
            string compressed = compressFile(content, root, codes);
            cout << "  原始大小：" << content.length() << " 字节" << endl;
            cout << "  压缩后二进制长度：" << compressed.length() << " 位" << endl;
            cout << "  理论压缩率：" << fixed << setprecision(2)
                 << (1.0 - compressed.length() / 8.0 / content.length()) * 100 << "%" << endl;

            // 保存压缩文件
            compressedFilename = "compressed.txt";
            writeCompressedFile(compressed, compressedFilename);
            cout << "  ✓ 压缩文件已保存至：" << compressedFilename << endl;

            // 显示前 100 位压缩编码
            cout << "\n  压缩编码预览 (前 100 位):" << endl;
            cout << "  ";
            for (size_t i = 0; i < min((size_t)100, compressed.length()); i++)
            {
                cout << compressed[i];
                if ((i + 1) % 10 == 0)
                    cout << " ";
            }
            cout << endl;
            break;
        }

        case 2: // 解压文件
        {
            cout << "\n【文件解压】" << endl;

            try
            {
                // 读取压缩文件
                if (compressedFilename.empty())
                {
                    compressedFilename = "compressed.txt";
                }
                string compressed = readCompressedFile(compressedFilename);
                cout << "  读取压缩文件：" << compressedFilename << endl;
                cout << "  二进制数据长度：" << compressed.length() << " 位" << endl;

                // 解压文件
                string decompressed = decompressFile(compressed, root);
                cout << "  解压后大小：" << decompressed.length() << " 字节" << endl;

                // 验证解压结果
                if (decompressed == content)
                {
                    cout << "  ✅ 解压验证成功！内容与原文一致。" << endl;
                }
                else
                {
                    cout << "  ⚠️ 警告：解压内容与原文不一致！" << endl;
                }

                // 保存解压文件
                decompressedFilename = "decompressed.txt";
                writeStringToFile(decompressed, decompressedFilename);
                cout << "  ✓ 解压文件已保存至：" << decompressedFilename << endl;

                // 显示解压内容预览
                cout << "\n  解压内容预览 (前 200 字符):" << endl;
                cout << "  ";
                for (size_t i = 0; i < min((size_t)200, decompressed.length()); i++)
                {
                    cout << decompressed[i];
                }
                if (decompressed.length() > 200)
                {
                    cout << "... (更多内容请查看文件)";
                }
                cout << endl;
            }
            catch (const exception &e)
            {
                cerr << "  错误：" << e.what() << endl;
            }
            break;
        }

        case 3: // 显示哈夫曼编码表
        {
            displayHuffmanCodes(codes);
            break;
        }

        case 4: // 退出
        {
            cout << "\n感谢使用，再见！" << endl;
            break;
        }

        default:
        {
            cout << "\n⚠️ 无效选择，请输入 1-4 之间的数字" << endl;
            break;
        }
        }
    } while (choice != 4);

    cout << "\n按回车键退出..." << endl;
    cin.get();
    return 0;
}