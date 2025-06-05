#include "site_recommend.h"
#include "ui_site_recommend.h"
#include "diarywindow.h"
#include "tool_class/read_data.h"
#include "kmp_search.h"
#include "top_k_algorithm.h"
#include <iomanip>
#include <QtWidgets/QMessageBox>
#include <QCompleter>

site_recommend::site_recommend(user u, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::site_recommend)
    , u(u)
    , currentPage(0)
    , itemsPerPage(10)
{
    ui->setupUi(this);
    this->setWindowTitle("景点推荐");

    // 设置按钮组
    this->locations = read_data::getInstance().read_location_data();
    this->locationlists=this->locations;
    button_group = new QButtonGroup(this);
    button_group->addButton(ui->heat_button);
    button_group->addButton(ui->score_button);
    button_group->addButton(ui->food_button);
    button_group->addButton(ui->sport_button);
    button_group->addButton(ui->study_button);
    button_group->addButton(ui->trip_button);
    button_group->setExclusive(true);
    ui->heat_button->setChecked(true);

    ui->search_line->setPlaceholderText("请输入搜索内容");
    ui->locationLists->setSpacing(8);

    QStringList nameList;
    for (const auto& l : locations)  {
        nameList.append(QString::fromStdString(l.title));
    }
    QCompleter *completer = new QCompleter(nameList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    ui->search_line->setCompleter(completer);
    connect(button_group,&QButtonGroup::buttonClicked,this,&site_recommend::changeBool);
    connect(button_group,&QButtonGroup::buttonClicked,this,&site_recommend::sort_site);
    emit button_group->buttonClicked(button_group->checkedButton());
    qDebug() << "景点推荐界面加载完成";

    // 连接信号槽

    connect(ui->search_site,&QPushButton::clicked,this,&site_recommend::on_search_site_button_clicked);
    connect(ui->return_button, &QPushButton::clicked,this, &site_recommend::on_return_button_clicked);

}

site_recommend::~site_recommend()
{
    delete ui;
    emit windowclose();
}


void site_recommend::updatePagination(bool keepPage)
{
    qDebug() << "---- 分页更新开始 ----";
    qDebug() << "当前数据总量:" << locationlists.size();
    qDebug() << "请求保持页码:" << keepPage;
    qDebug() << "当前页码(before):" << currentPage;

    // 计算总页数
    int totalPages = getTotalPages();
    if (totalPages == 0) totalPages = 1;  // 至少1页

    // 修正当前页码
    if (!keepPage) {
        currentPage = 0;
    } else {
        // 使用std::clamp确保页码在有效范围内
        currentPage = std::max(0, std::min(currentPage, totalPages - 1));
    }

    qDebug() << "修正后页码:" << currentPage;
    qDebug() << "总页数:" << totalPages;

    // 更新按钮状态
    ui->previous_page->setEnabled(currentPage > 0 && !topkuse);
    ui->next_page->setEnabled(currentPage < totalPages - 1 && !topkuse);

    // 获取分页数据
    int startIdx = currentPage * itemsPerPage;
    int endIdx = std::min(startIdx + itemsPerPage, (int)locationlists.size());

    qDebug() << "分页范围:" << startIdx << "-" << endIdx;
    qDebug() << "now topklocations size is:" << topklocations.size();
    pagedLocations.clear();
    if (startIdx < locationlists.size()) {
        pagedLocations.assign(topklocations.begin() + startIdx,
                              topklocations.begin() + endIdx);
    }

    // 更新显示
    show_location(pagedLocations);
    if(!topkuse){
        ui->page_label->setText(
            QString("第 %1 页/共 %2 页 (共%3条)")
                .arg(currentPage + 1)
                .arg(totalPages)
                .arg(locationlists.size())
            );
    } else {
        ui->page_label->clear();
    }

    qDebug() << "---- 分页更新完成 ----\n";
}
void site_recommend::on_next_page_clicked()
{
    qDebug() << "点击下一页前 - 当前页:" << currentPage;

    int totalPages = getTotalPages();
    if (currentPage + 1 < totalPages) {
        currentPage++;
        qDebug() << "下一页有效跳转 - 新页码:" << currentPage;
        updatePagination(!topkuse);
    } else {
        qDebug() << "已是最后一页，无法继续下一页";
    }
}

void site_recommend::on_previous_page_clicked()
{
    qDebug() << "点击上一页前 - 当前页:" << currentPage;

    if (currentPage > 0) {
        currentPage--;
        qDebug() << "上一页有效跳转 - 新页码:" << currentPage;
        updatePagination(!topkuse);
    } else {
        qDebug() << "已是第一页，无法继续上一页";
    }
}


void site_recommend::on_return_button_clicked()
{
    emit return_to_main_window();  // 发射返回信号
    this->hide();              // 隐藏当前窗口
}

void site_recommend::show_location(std::vector<location> locations)
{
    ui->locationLists->clear();

    for (const location &l : locations) {
        std::ostringstream oss;

        // 设置左对齐
        oss << std::left;

        // 设置固定宽度格式
        oss << std::setw(40) << l.title                        // 景点名称
            << std::setw(15) << ("热度: " + QString::number(l.popularity).toStdString())
            << std::setw(15) << ("评分: " + QString::number(l.score, 'f', 1).toStdString())  // 保留1位小数
            << std::setw(15) << ("运动: " + QString::number(l.sport, 'f', 1).toStdString())
            << std::setw(15) << ("美食: " + QString::number(l.food, 'f', 1).toStdString())
            << std::setw(15) << ("旅游: " + QString::number(l.trip, 'f', 1).toStdString())
            << std::setw(15) << ("学习: " + QString::number(l.study, 'f', 1).toStdString());

        QListWidgetItem *item = new QListWidgetItem(ui->locationLists);



        item->setText(QString::fromStdString(oss.str()));
        item->setData(Qt::UserRole, QVariant::fromValue(l));


    }


}

void site_recommend::on_search_site_button_clicked()
{
    QString searchText = ui->search_line->text();

    if(searchText.isEmpty()) {
        QMessageBox::information(this, "提示", "请输入搜索关键词");
        return;
    }

    try {
        auto results = search_site(searchText.toStdString(), locations);

        if(results.empty()) {
            QMessageBox::information(this, "提示", "未找到匹配景点");
        }

        locationlists = results;
        emit button_group->buttonClicked(button_group->checkedButton());

    } catch(const std::exception &e) {
        qCritical() << "搜索出错:" << e.what();
        QMessageBox::critical(this, "错误", "搜索过程中发生错误");
    }

}


void site_recommend::sort_site()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    int totalItems = locationlists.size();
    QString str = button_group->checkedButton()->text();
    if(topkuse){
        qDebug() << "此时仅排序出前十个";
        totalItems = 10;
    }
    if(!str.compare("按学习分数排序")) {
        topklocations = getTopK(locationlists, totalItems, [](const location &a, const location &b) {
            return a.study > b.study;
        });
    }
    else if(!str.compare("按美食分数排序")) {
        topklocations = getTopK(locationlists, totalItems, [](const location &a, const location &b) {
            return a.food > b.food;
        });
    }
    else if(!str.compare("按旅游分数排序")) {
        topklocations = getTopK(locationlists, totalItems, [](const location &a, const location &b) {
            return a.trip > b.trip;
        });
    }
    else if(!str.compare("按运动分数排序")) {
        topklocations = getTopK(locationlists, totalItems, [](const location &a, const location &b) {
            return a.sport > b.sport;
        });
    }
    else if(!str.compare("按热度分数排序")) {
        topklocations = getTopK(locationlists, totalItems, [](const location &a, const location &b) {
            return a.popularity > b.popularity;
        });
    }
    else if(!str.compare("按评分分数排序")) {
        topklocations = getTopK(locationlists, totalItems, [](const location &a, const location &b) {
            return a.score > b.score;
        });
    }
    updatePagination(!topkuse);
    QApplication::restoreOverrideCursor();
}


void site_recommend::on_refresh_button_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    locationlists = locations;
    emit button_group->buttonClicked(button_group->checkedButton());
    QApplication::restoreOverrideCursor();
}


std::vector<location> site_recommend::search_site(const std::string str, std::vector<location> locations)
{
    std::vector<location> newlocations;
    const int max_results = 100;

    qDebug() << "开始搜索，关键词:" << QString::fromStdString(str);
    qDebug() << "总数据量:" << locations.size();

    for(const location &l : locations) {
        if(KMP::kmpMatch(l.title, str)) {
            qDebug() << "找到匹配:" << QString::fromStdString(l.title);
            newlocations.push_back(l);

            if(newlocations.size() >= max_results) {
                break;
            }
        }
    }

    qDebug() << "搜索完成，结果数:" << newlocations.size();
    return newlocations;
}

void site_recommend::closeEvent(QCloseEvent *event) {
    emit windowclose(); // 发出信号
}

void site_recommend::on_pushButton_clicked()
{
    topklocations = locationlists;
    topkuse = false;
    sort_site();
}


void site_recommend::on_locationLists_itemActivated(QListWidgetItem *item)
{
    std::string title = item->data(Qt::UserRole).value<location>().title;
    diarywindow *dw = new diarywindow(u, QString::fromStdString(title));
    dw->show();
}

