#include "haffuman.h"
using namespace std;
// 哈夫曼树结点结构体
typedef struct HaffumanNode {
  int value;
  int kind; // 1 为带字符结点，0为树的非叶子结点
  char ch;
  HaffumanNode *ltree;
  HaffumanNode *rtree;
} Hnode;
// 优先队列的比较器
struct CompareHnode {
  bool operator()(const Hnode *lhs, const Hnode *rhs) const {
    return lhs->value > rhs->value; // 升序排序
  }
};

// 优先队列q,用于在哈夫曼编码中获取权值最小的结点
priority_queue<Hnode *, vector<Hnode *>, CompareHnode> q;

// 基础函数
map<char, int> ReadText(string in);
void compressText(Hnode *root, map<char, string> cl, string in1, string out1);
void deCompress(Hnode *root, map<char, string> cl, string out1);

// 哈夫曼树相关函数
void creatTree(Hnode *&root);
string searchCode(char ch, Hnode *node, string s);
char searchChar(ifstream &in, Hnode *root);
map<char, string> codeList(map<char, int> data, Hnode *root);

// 搜索
void searchWord(string m, Hnode *root, string out1);
void preProcess(int *, bool *, int *, string s);

//---------------------------------------------------------------------------

int main(int argc, char *argv[]) {
  string in = "text.txt";
  string out = "CompressText.txt";
  for (int i = 0; i < argc; i++) { // 根据命令行参数更改输入输出路径
    if (i + 1 < argc && argv[i] == string("-i"))
      in = argv[i + 1];
    if (i + 1 < argc && argv[i] == string("-o"))
      out = argv[i + 1];
  }
  map<char, int> data = ReadText(in); // 获取输入文本字符频率
  for (const auto &pair : data) { // 建立叶子结点，并加入优先队列中
    Hnode *node = new Hnode();
    node->ch = pair.first;
    node->kind = 1;
    node->value = pair.second;
    node->ltree = node->rtree = NULL;
    q.push(node);
  }
  Hnode *root;
  creatTree(root);                                // 建立哈夫曼树
  map<char, string> CodeL = codeList(data, root); // 获取文本字符对应的哈夫曼编码
  compressText(root, CodeL, in, out); // 根据编码进行文本压缩
  deCompress(root, CodeL, out); // 根据编码和压缩文件进行解压缩
  string m = argv[1];
  searchWord(m, root, out); // 搜索输入的单词
  cout << "end" << endl;
  return 0;
}

//-----------------------------------------------------------------------------------

map<char, int> ReadText(string in) {
  map<char, int> s;
  ifstream inFile(in);
  if (!inFile) { // 考虑打开失败的情况
    cout << "打开文件失败" << endl;
    return s;
  }
  char k;
  while (inFile.get(k)) {
    if (int(k) < 0)
      continue;
    s[k]++;
  }
  inFile.close();
  return s;
}

void compressText(Hnode *root, map<char, string> cl, string in1, string out1) {
  char ch;
  ifstream in(in1);
  ofstream out(out1);
  if (out.is_open()) {
    int countword = 0, coutnumber = 0;
    while (in.get(ch)) {
      countword++;
      string s = cl[ch];
      coutnumber += s.length();
      out << s;
    }
    double rate = double(coutnumber) / double(countword * 7); // 输出文件压缩率
    cout << "文件的压缩率为: " << rate << endl;
  }
  in.close();
  out.close();
}

void deCompress(Hnode *root, map<char, string> cl, string out1) {
  ifstream in(out1);
  ofstream out("DeCompressText.txt");
  char ch;
  Hnode *node;
  while (in.get(ch)) {
    node = root;
    if (ch == '0')
      node = node->ltree;
    else
      node = node->rtree;
    while (node->kind != 1) {
      in.get(ch);
      if (ch == '0')
        node = node->ltree;
      else
        node = node->rtree;
    }
    ch = node->ch;
    out << ch;
  }
  in.close();
  out.close();
}

void creatTree(Hnode *&root) {
  Hnode *node1;
  Hnode *node2;
  node1 = q.top();
  while (!q.empty()) {
    node1 = q.top();
    q.pop();
    if (q.empty()) {
      root = node1;
      break;
    }
    node2 = q.top();
    q.pop();
    Hnode *node = new Hnode();
    node->value = node1->value + node2->value;
    node->kind = 0;
    node->ltree = node1;
    node->rtree = node2;
    q.push(node);
  }
}

string searchCode(char ch, Hnode *node, string s) {
  if (node->kind == 1) {
    if (node->ch == ch) {
      // cout<<ch<<" "<<s<<endl;
      return s;
    } else
      return "a";
  } else {
    string a =
        searchCode(ch, node->ltree,
                   s + "0"); // 通过递归的方式dfs搜索哈夫曼树查询目标字符位置
    string b = searchCode(ch, node->rtree, s + "1");
    if (a != "a")
      return a;
    else if (b != "a")
      return b;
    else
      return "a";
  }
}

map<char, string> codeList(map<char, int> data, Hnode *root) {
  ofstream outFile("CodeList");
  map<char, string> m;
  if (outFile.is_open()) {
    outFile << "编码列表为" << endl;
    for (const auto &pair : data) {
      string code = "\0";
      code = searchCode(pair.first, root, code);
      m.insert({pair.first, code});
      if (pair.first != '\n')
        outFile << pair.first << " " << code << endl;
      else
        outFile << "\n" << " " << code << endl;
    }
    outFile.close();
  }
  return m;
}

char searchChar(ifstream &in,
                Hnode *root) { // 用输入流in的引用，保证对输入文本读取的连续
  char ch;
  while (in.get(ch)) {
    if (ch == '0')
      root = root->ltree;
    else
      root = root->rtree;
    if (root->kind == 1)
      return root->ch;
  }
  return 0;
}

//------------------------------------------------------------------------

void searchWord(string m, Hnode *root, string out1) {
  int *badChar = new int[256];
  bool *prefix = new bool[20];
  int *suffix = new int[20];
  for (int i = 0; i < 256; i++)
    badChar[i] = -1;                      // 对坏字符数组预处理
  preProcess(badChar, prefix, suffix, m); // 对模板字符串预处理
  string mstr;
  int length = m.length();
  ifstream in(out1);
  ofstream out("Location.txt");
  out << "查询的单词为" << " " << m << endl;
  char ch = searchChar(in, root);
  for (int i = 0; i < length;
       i++) { // 通过获取所需长度的文本字符串进行比对，部分解压
    mstr.push_back(ch);
    ch = searchChar(in, root);
  }
  int count = length, number = length - 1;
  int count1 = 0;
  while (ch != 0) {
    while (m[number] == mstr[number] && number >= 0)
      number--;
    if (number == length - 1 && badChar[int(mstr[number])] != -1) { // 坏字符情况
      int k1 = badChar[int(mstr[number])] + 1;
      mstr = mstr.substr(length - badChar[int(mstr[number])] - 1);
      for (int i = 0; i < length - k1; i++) {
        mstr.push_back(ch);
        count++;
        ch = searchChar(in, root);
      }
    } else if (number == -1) { // 查询成功
      out << "于第" << count << "处查询到" << endl;
      mstr.clear();
      count1++;
      for (int i = 0; i < length; i++) {
        mstr.push_back(ch);
        count++;
        ch = searchChar(in, root);
      }
    } else {
      int w = length - 1 - number; // 好字符情况
      if (suffix[w] != -1) {
        mstr = mstr.substr(0, w + suffix[w] + 1);
        for (int i = 0; i < length - w - suffix[w]; i++) {
          mstr.push_back(ch);
          count++;
          ch = searchChar(in, root);
        }
      } else if (prefix[w]) {
        mstr.substr(0, w);
        for (int i = 0; i < length - w + 1; i++) {
          mstr.push_back(ch);
          count++;
          ch = searchChar(in, root);
        }
      } else { // 无匹配则整个跳过
        mstr.clear();
        for (int i = 0; i < length; i++) {
          mstr.push_back(ch);
          count++;
          ch = searchChar(in, root);
        }
      }
    }
    number = length - 1;
  }
  if (!count1)
    out << "无结果" << endl;
  else
    out << "共查找到" << count1 << "次" << endl;
  in.close();
  out.close();
}

void preProcess(int *badChar, bool *prefix, int *suffix, string s) {
  int length = s.length();
  for (int i = 0; i < length; i++) { // 对好字符的两个数组预处理
    badChar[int(s[i])] = i;
    prefix[i] = false;
    suffix[i] = -1;
  }
  for (int i = 0; i < length - 1; i++) {
    int j = i;
    int k = 0;
    while (j >= 0 && s[j] == s[length - 1 - k]) {
      --j;
      ++k;
      suffix[k] = j + 1;
    }
    if (j == -1)
      prefix[k] = true; // 前缀判断
  }
}
