#include "site_recommend.h"
#include "ui_site_recommend.h"
#include "tool_class/read_data.h"
#include "kmp_search.h"
#include "top_k_algorithm.h"

site_recommend::site_recommend(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::site_recommend)
{
    ui->setupUi(this);

    // 设置按钮组
    this->locations = read_data::getInstance().read_location_data();
    this->locationlists=this->locations;
    button_group = new QButtonGroup(this);
    button_group->addButton(ui->search_site);
    button_group->addButton(ui->heat_button);
    button_group->addButton(ui->score_button);
    button_group->addButton(ui->food_button);
    button_group->addButton(ui->sport_button);
    button_group->addButton(ui->study_button);
    button_group->addButton(ui->trip_button);
    button_group->setExclusive(true);
    ui->trip_button->setChecked(true);
    connect(button_group,&QButtonGroup::buttonClicked,this,&site_recommend::choose_sort_model);
    emit button_group->buttonClicked(button_group->checkedButton());
    qDebug() << "景点推荐界面加载完成";

    // 连接信号槽

    connect(ui->search_site,&QPushButton::clicked,this,&site_recommend::on_search_site_button_clicked);


}

site_recommend::~site_recommend()
{
    delete ui;
    emit windowclose();
}

void site_recommend::show_location(std::vector<location> locations)
{
    ui->locationLists->clear();

    // 定义每一列的固定宽度
    const int titleWidth = 20;    // 景点名称宽度
    const int fieldWidth = 10;    // 各评分字段宽度

    for (const location &l : locations)
    {
        // 使用 QString::arg() 和 leftJustified() 实现对齐
        QString str = QString("%1").arg(QString::fromStdString(l.title).leftJustified(titleWidth, ' ')) +
                      "热度:" + QString::number(l.popularity).leftJustified(fieldWidth, ' ') +
                      "评分:" + QString::number(l.score).leftJustified(fieldWidth, ' ') +
                      "运动:" + QString::number(l.sport).leftJustified(fieldWidth, ' ') +
                      "美食:" + QString::number(l.food).leftJustified(fieldWidth, ' ') +
                      "旅游:" + QString::number(l.trip).leftJustified(fieldWidth, ' ') +
                      "学习:" + QString::number(l.study).leftJustified(fieldWidth, ' ');

        QListWidgetItem *item = new QListWidgetItem(ui->locationLists);
        item->setText(str);
        item->setData(Qt::UserRole, QVariant::fromValue(l));
    }
}


void site_recommend::on_search_site_button_clicked()
{
    this->locationlists = search_site(ui->search_line->toPlainText().toStdString(), locations);
    emit button_group->buttonClicked(button_group->checkedButton());
}

void site_recommend::choose_sort_model(){             //排序方法选择
    int k = 10;
    QString str =button_group->checkedButton()->text();
    std::vector<location> ls;
    if(!str.compare("按学习分数排序"))
    {
        ls = getTopK(this->locationlists, k, [](const location &a, const location &b)
        {
            return a.study > b.study; // 按学习分数排序
        });
    }
    else if(!str.compare("按美食分数排序"))
    {
        ls = getTopK(this->locationlists, k, [](const location &a, const location &b)
        {
            return a.food > b.food; // 按美食分数排序
        });
    }
    else if(!str.compare("按旅游分数排序"))
    {
        ls = getTopK(this->locationlists, k, [](const location &a, const location &b)
        {
            return a.trip > b.trip; // 按旅游分数排序
        });
    }
    else if(!str.compare("按运动分数排序"))
    {
        ls = getTopK(this->locationlists, k, [](const location &a, const location &b)
        {
            return a.sport > b.sport; // 按运动分数排序
        });
    }
    else if(!str.compare("按热度分数排序"))
    {
        ls = getTopK(this->locationlists, k, [](const location &a, const location &b)
        {
            return a.popularity > b.popularity; // 按热度评分排序
        });
    }
    else if(!str.compare("按评分分数排序"))
    {
        ls = getTopK(this->locationlists, k, [](const location &a, const location &b)
        {
            return a.score > b.score; // 按评分分数排序
        });
    }
    show_location(ls);
}

void site_recommend::on_refresh_button_clicked()
{
    this->locations = read_data::getInstance().read_location_data();
    this->locationlists = this->locations;
    emit button_group->buttonClicked(button_group->checkedButton());
}


std::vector<location> site_recommend::search_site(const std::string str, std::vector<location> locations)
{
    std::vector<location> newlocations;
    const int max_results = 10; // 最多返回10个结果

    for(const location &l : locations) {
        if(KMP::kmpMatch(l.title, str)) {
            newlocations.push_back(l);
            qDebug() << "找到匹配景点: " << QString::fromStdString(l.title);

            // 如果已经找到足够多的结果，提前结束循环
            if(newlocations.size() >= max_results) {
                break;
            }
        }
    }

    qDebug() << "共找到" << newlocations.size() << "个匹配景点";
    return newlocations;
}


