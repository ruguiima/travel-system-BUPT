#include "diarywindow.h"
#include "ui_diarywindow.h"
#include "tool_class/read_data.h"

diarywindow::diarywindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::diarywindow),write_widget()
{
    ui->setupUi(this);
    button_grooup = new QButtonGroup(this);
    button_grooup->addButton(ui->scoreorder);
    button_grooup->addButton(ui->popularityorder);
    button_grooup->setExclusive(true);
    diarys = read_data::getInstance().read_diary_data();
    locations = read_data::getInstance().read_location_data();
    connect(button_grooup, &QButtonGroup::buttonClicked, this, &diarywindow::choose_sort_model);
    show_diary(diarys);
}

diarywindow::~diarywindow()
{
    delete ui;
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
    write_widget = new writewidget(nullptr, l, id);
    connect(write_widget, &writewidget::closewidget, this, &diarywindow::show);
    write_widget->show();
    this->hide();
}

void diarywindow::choose_sort_model(){             //排序方法选择
    int k;
    QString str =button_grooup->checkedButton()->text();

    if(!str.compare("按热度排序"))
        k = 1;
    else
        k = 2;
    qDebug() << k;
}

std::vector<diary> diarywindow::search_title(const std::string str, std::vector<diary> diarys){
    std::vector<diary> newdiarys;
    for(const diary &d : diarys)
        if(d.title.find(str))
            newdiarys.push_back(d);
    return newdiarys;

}

std::vector<diary> diarywindow::search_site(const std::string str, std::vector<diary> diarys, std::vector<location> locations){
    std::vector<diary> newdiarys;
    int id;
    for(const location &l : locations)
        if(!l.title.compare(str)){
            id = l.id;
            break;
        }

    for(const diary &d : diarys){
        if(d.site_id == id)
            newdiarys.push_back(d);
    }
    return newdiarys;
}


void diarywindow::show_diary(std::vector<diary> diarys)             //日记列表初始化
{
    ui->diaryslist->clear();
    // QVBoxLayout *layout = new QVBoxLayout(ui->diaryslist);
    for(diary d : diarys){
        std::string str = d.title + "\t景点:" + "未知" + "\t作者:" + d.author_name;
        QListWidgetItem *item = new QListWidgetItem(ui->diaryslist);
        item->setText(QString::fromStdString(str));
        item->setData(Qt::UserRole, QVariant::fromValue(d)); // 保存额外的信息
    }
}



void diarywindow::on_sitesearch_clicked()
{
    std::vector<diary> adiarys = search_site(ui->searchbar->toPlainText().toStdString(), diarys, locations);
    diarywindow::show_diary(adiarys);
}




void diarywindow::on_titlesearch_clicked()
{
    std::vector<diary> adiarys = search_title(ui->searchbar->toPlainText().toStdString(), diarys);
    diarywindow::show_diary(adiarys);
}



