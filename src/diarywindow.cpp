#include "diarywindow.h"
#include "ui_diarywindow.h"
#include "tool_class/read_data.h"
#include "kmp_search.h"
#include "top_k_algorithm.h"

diarywindow::diarywindow(user u, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::diarywindow),write_widget()
{
    ui->setupUi(this);
    this->u = u;
    // qDebug() << "当前登录用户为：" << u.account;
    button_grooup = new QButtonGroup(this);
    button_grooup->addButton(ui->scoreorder);
    button_grooup->addButton(ui->popularityorder);
    button_grooup->setExclusive(true);
    this->locations = read_data::getInstance().read_location_data();
    this->diarys = read_data::getInstance().read_diary_data();
    this->diarylist = this->diarys;
    ui->popularityorder->setChecked(true);
    connect(button_grooup, &QButtonGroup::buttonClicked, this, &diarywindow::choose_sort_model);
    emit button_grooup->buttonClicked(button_grooup->checkedButton());
    qDebug() << "日记页面加载完成";
}

diarywindow::~diarywindow()
{
    delete ui;
    emit windowclose();
}


void diarywindow::on_diaryslist_itemActivated(QListWidgetItem *item)          //日记查看窗口
{
    diaryread *dr = new diaryread(item->data(Qt::UserRole).value<diary>());
    connect(dr, &diaryread::closewidget, this, &diarywindow::show);
    dr->show();
}

void diarywindow::on_writediary_clicked()            //进入写日志窗口
{
    location_choose_widget = new location_choose(locations);
    location_choose_widget->show();
    connect(location_choose_widget, &location_choose::location_pass, this, &diarywindow::open_write_widget);
    location_choose_widget->exec();
}

void diarywindow::open_write_widget(const QString l, const int id){
    write_widget = new writewidget(u, nullptr, l, id);
    connect(write_widget, &writewidget::closewidget, this, &diarywindow::show);
    write_widget->show();
    this->hide();
}

void diarywindow::choose_sort_model(){             //排序方法选择
    int k = 10;
    QString str =button_grooup->checkedButton()->text();
    std::vector<diary> ds;
    if(!str.compare("按热度排序")){
        ds = getTopK(this->diarylist, k, [](const diary &a, const diary &b) {
            return a.popularity > b.popularity; // 按热度排序
        });
    }
    else
    {
        ds = getTopK(this->diarylist, k, [](const diary &a, const diary &b) {
            return a.score > b.score; // 按评分排序
        });
    }
    show_diary(ds);
}

void diarywindow::show_diary(std::vector<diary> diarys)             //日记列表初始化
{
    ui->diaryslist->clear();
    // QVBoxLayout *layout = new QVBoxLayout(ui->diaryslist);
    for(diary d : diarys){
        std::string str = d.title + "\t景点:" + d.site_name + "\t作者:" + d.author_name + "\t 热度："
                          + QString::number(d.popularity).toStdString() + "\t 评分：" + QString::number(d.score).toStdString();
        // qDebug() << QString::fromStdString(str);
        QListWidgetItem *item = new QListWidgetItem(ui->diaryslist);
        item->setText(QString::fromStdString(str));
        item->setData(Qt::UserRole, QVariant::fromValue(d)); // 保存额外的信息
    }
}



void diarywindow::on_sitesearch_clicked()
{
    this->diarylist = search_site(ui->searchbar->toPlainText().toStdString(), diarys, locations);
    emit button_grooup->buttonClicked(button_grooup->checkedButton());
}


void diarywindow::on_titlesearch_clicked()
{
    this->diarylist = search_title(ui->searchbar->toPlainText().toStdString(), diarys);
    emit button_grooup->buttonClicked(button_grooup->checkedButton());
}

void diarywindow::on_refresh_clicked()
{
    this->diarys = read_data::getInstance().read_diary_data();
    this->diarylist = this->diarys;
    emit button_grooup->buttonClicked(button_grooup->checkedButton());
}

std::vector<diary> diarywindow::search_title(const std::string str, std::vector<diary> diarys){
    std::vector<diary> newdiarys;
    for(const diary &d : diarys)
        if(KMP::kmpMatch(d.title,str)){
            newdiarys.push_back(d);
            qDebug() << "搜到的日记名称：" << QString::fromStdString(d.title);
        }
    return newdiarys;

}

std::vector<diary> diarywindow::search_site(const std::string str, std::vector<diary> diarys, std::vector<location> locations){
    std::vector<diary> newdiarys;
    int id;
    for(const location &l : locations)
        if(KMP::kmpMatch(l.title,str)){
            id = l.id;
            qDebug() << "搜到的景点id " << id;
            break;
        }

    for(const diary &d : diarys){
        if(d.site_id == id)
            newdiarys.push_back(d);
    }
    return newdiarys;
}
