#ifndef HUFFMANCODING_H
#define HUFFMANCODING_H

#include "simple_class/diary.h"
#include <QString>
#include <map>
#include <queue>
#include <vector>
#include <QStringList>

struct HaffumanNode {
    int value;                         // 节点的频率值
    int kind;                          // 1 为带字符节点，0 为树的非叶子节点
    QChar ch;                           // 存储的字符
    HaffumanNode* ltree;              // 左子树指针
    HaffumanNode* rtree;              // 右子树指针

    // 字符节点构造函数
    HaffumanNode(QChar character, int val)
        : value(val), kind(1), ch(character), ltree(nullptr), rtree(nullptr) {}

    // 非叶子节点构造函数
    HaffumanNode(int val, HaffumanNode* left, HaffumanNode* right)
        : value(val),  kind(0), ltree(left), rtree(right) {}
};

// 优先队列的比较器
struct CompareHnode {
    bool operator()(const HaffumanNode* lhs, const HaffumanNode* rhs) const {
        return lhs->value > rhs->value; // 升序排序
    }
};

class HuffmanCoding
{
private:
    std::priority_queue<HaffumanNode*, std::vector<HaffumanNode*>, CompareHnode> q;
    HaffumanNode* root;
    std::map<QChar, QString> codes;
    std::map<QChar, int> data;
    QString codestirng;
    diary d;

    void createTree();
    QString searchCode(QChar ch, HaffumanNode* node, QString s);
    std::map<QChar, int> generateFrequencyMap(const QString& input);
    std::map<QChar, QString> codeList(const std::map<QChar, int>& data);
    QString getDecompress(QString str);

public:
    HuffmanCoding() : root(nullptr) {}
    void compress(const diary d);
    diary load_diary(const QString& input);
    int save_diary(diary d);
};

#endif // HUFFMANCODING_H
