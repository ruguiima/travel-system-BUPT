#include "include/tool_class/HuffmanCoding.h"

#include <QTextStream>
#include <qfile.h>
#include <qfiledialog.h> 

// 生成字符频率映射
std::map<QChar, int> HuffmanCoding::generateFrequencyMap(const QString& input) {
    std::map<QChar, int> frequencies;
    for (QChar ch : input) {
        frequencies[ch]++;
    }
    return frequencies;
}

// 创建哈夫曼树
void HuffmanCoding::createTree() {
    while (q.size() > 1) {
        HaffumanNode* left = q.top(); q.pop();
        HaffumanNode* right = q.top(); q.pop();
        HaffumanNode* parent = new HaffumanNode(left->value + right->value, left, right);
        q.push(parent);
    }
    root = q.top(); // 根节点
}

// 生成编码
std::map<QChar, QString> HuffmanCoding::codeList(const std::map<QChar, int>& data) {
    std::map<QChar, QString> codes;
    for (const auto& pair : data) {
        QString code = searchCode(pair.first, root, "");
        codes.insert({pair.first, code});
    }
    return codes;
}

// 哈夫曼编码搜索
QString HuffmanCoding::searchCode(QChar ch, HaffumanNode* node, QString s) {
    if (!node) return "";
    if (node->kind == 1) {
        if (node->ch == ch) return s;
        return "";
    }

    QString leftResult = searchCode(ch, node->ltree, s + "0");
    if (!leftResult.isEmpty()) return leftResult;

    return searchCode(ch, node->rtree, s + "1");
}

// 文本压缩
void HuffmanCoding::compress(const diary d) {
    this->d = d;
    QString output;
    data = generateFrequencyMap(QString::fromStdString(d.context)); // 获取字符频率
    for(auto pair : data)
        qDebug() << pair.first << " " << pair.second;
    qDebug() << "1231231";
    for (const auto& pair : data) {
        HaffumanNode* node = new HaffumanNode(pair.first, pair.second);
        q.push(node);
    }
    createTree(); // 构建哈夫曼树
    codes = codeList(data); // 获取编码
    output.clear(); // 清空输出字符串
    for (QChar ch : QString::fromStdString(d.context)) {
        output += codes.at(ch); // 连接编码
    }
    this->codestirng = output;
}

// 文本解压缩
diary HuffmanCoding::load_diary(const QString& fileName) {
    qDebug() << "正在打开" << fileName;
    QFile file(fileName);
    QTextStream in(&file);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        QTextStream in(&file);
    else
        qDebug() << "未打开成功";
    QString line = in.readLine();
    QStringList code = line.split(' ', Qt::SkipEmptyParts);
    int count = 0;
    root = new HaffumanNode(0, nullptr, nullptr); // 创建根节点
    //创建哈夫曼树
    while(count < code.length()){
        QChar character = code[count].at(0);
        QString code1 = code[++count];
        qDebug() << character << " " << code1;
        codes[character] = code1;

        HaffumanNode* current = root;
        // 遍历编码中的每个字符
        for (QChar bit : code1) {
            if (bit == '0') {
                // 创建左子节点
                if (!current->ltree) {
                    current->ltree = new HaffumanNode(0, nullptr, nullptr);
                }
                qDebug() << "0";
                current = current->ltree; // 移动到左子节点
            } else if (bit == '1') {
                // 创建右子节点
                if (!current->rtree) {
                    current->rtree = new HaffumanNode(0, nullptr, nullptr);
                }
                qDebug() << "1";
                current = current->rtree; // 移动到右子节点
            }
        }
        // 在叶子节点处设置字符
        current->ch = character;
        current->kind = 1; // 设置为带字符的叶子节点
        count++;
    }
    d.author_name = in.readLine().toStdString();
    d.site_name = in.readLine().toStdString();
    d.title = in.readLine().toStdString();
    line = in.readLine();
    d.context = getDecompress(line).toStdString();
    d.image_path = "0";
    file.close();
    return d;
}

QString HuffmanCoding::getDecompress(QString str){
    QString output;
    HaffumanNode* node = root;
    for (QChar ch : str) {
        node = (ch == '0') ? node->ltree : node->rtree;
        if (node->kind == 1) {
            output += node->ch; // 添加字符到输出
            node = root; // 返回根节点
        }
    }
    return output;
}

int HuffmanCoding::save_diary(diary d) {
    compress(d);
    // 设置默认文件名和扩展名
    QString defaultFileName = "diary.travel";

    QString fileName = QFileDialog::getSaveFileName(
        nullptr, // 父窗口
        "保存文件", // 对话框标题
        defaultFileName, // 默认文件路径与文件名
        "文本文件 (*.travel);;所有文件 (*)" // 文件过滤器
        );

    // 检查用户是否选择了文件路径
    if (fileName.isEmpty()) {
        qDebug() << "用户取消了保存操作";
        return 0;
    }

    if (!fileName.endsWith(".travel", Qt::CaseInsensitive)) {
        fileName += ".travel"; // 添加扩展名
    }

    // 创建 QFile 对象
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "无法打开文件:" << file.errorString();
        return 0; // 返回错误代码
    }

    QTextStream out(&file);
    for (const auto& pair : codes){
        QString s = QString(pair.first);
        qDebug() << pair.first << " " << s;
        out << s << " " << pair.second << " ";
    }
    out << Qt::endl;
    out << QString::fromStdString(d.author_name) << Qt::endl;
    out << QString::fromStdString(d.site_name) << Qt::endl;
    out << QString::fromStdString(d.title) << Qt::endl;
    out << codestirng << Qt::endl;

    file.close();
    qDebug() << "成功写入" << fileName;
    return 1;
}
