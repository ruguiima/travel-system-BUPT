#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

#include "simple_class/diary.h"
#include <QString>
#include <map>
#include <queue>
#include <vector>
#include <QStringList>

// 哈夫曼树节点结构
struct HaffumanNode {
    int value;                       // 节点的频率值
    int kind;                        // 节点的类型，1 表示字符节点，0 表示非叶子节点
    QChar ch;                        // 存储的字符
    HaffumanNode* ltree;            // 左子树指针
    HaffumanNode* rtree;            // 右子树指针

    // 字符节点构造函数
    HaffumanNode(QChar character, int val)
        : value(val), kind(1), ch(character), ltree(nullptr), rtree(nullptr) {}

    // 非叶子节点构造函数
    HaffumanNode(int val, HaffumanNode* left, HaffumanNode* right)
        : value(val), kind(0), ltree(left), rtree(right) {}
};

// 优先队列的比较器，用于哈夫曼树节点的比较
struct CompareHnode {
    bool operator()(const HaffumanNode* lhs, const HaffumanNode* rhs) const {
        return lhs->value > rhs->value; // 按照频率值升序排序
    }
};

// 哈夫曼编码类
class HuffmanCoding
{
private:
    std::priority_queue<HaffumanNode*, std::vector<HaffumanNode*>, CompareHnode> q; // 存储哈夫曼节点的优先队列
    HaffumanNode* root;                  // 哈夫曼树的根节点
    std::map<QChar, QString> codes;      // 字符到哈夫曼编码的映射
    std::map<QChar, int> data;           // 字符到频率的映射
    QString codestirng;                  // 存储编码后的字符串
    diary d;                             // 日记对象

    // 私有函数：创建哈夫曼树
    void createTree();

    // 私有函数：搜索字符的哈夫曼编码
    QString searchCode(QChar ch, HaffumanNode* node, QString s);

    // 私有函数：生成字符频率映射
    std::map<QChar, int> generateFrequencyMap(const QString& input);

    // 私有函数：生成字符编码列表
    std::map<QChar, QString> codeList(const std::map<QChar, int>& data);

    // 私有函数：处理解压缩
    QString getDecompress(QString str);

public:
    // 默认构造函数
    HuffmanCoding() : root(nullptr) {}

    // 公共函数：压缩日记内容
    void compress(const diary d);

    // 公共函数：从文件中加载日记
    diary load_diary(const QString& input);

    // 公共函数：保存日记到文件
    int save_diary(diary d);
};

#endif // HUFFMANCODING_H
