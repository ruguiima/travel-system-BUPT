#include "diarywindow.h"
#include "ui_diarywindow.h"
#include "tool_class/read_data.h"
#include "kmp_search.h"
#include "top_k_algorithm.h"
#include <QCompleter>

diarywindow::diarywindow(user u, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::diarywindow),write_widget()
{
    ui->setupUi(this);
    this->setWindowTitle("旅游日记");
    this->u = u;
    button_grooup = new QButtonGroup(this);
    button_grooup->addButton(ui->scoreorder);
    button_grooup->addButton(ui->popularityorder);
    button_grooup->addButton(ui->mainsort);
    button_grooup->setExclusive(true);

    ui->diaryslist->setSpacing(8);
    ui->diaryslist->setFocus();
    ui->searchbar->installEventFilter(this);

    this->locations = read_data::getInstance().read_location_data();
    this->diarys = read_data::getInstance().read_diary_data();
    this->diarylist = this->diarys;

    QSet<QString> nameSet;
    for (auto l : locations)  {
        nameSet.insert(QString::fromStdString(l.title));
    }
    for (auto d : diarys)  {
        nameSet.insert(QString::fromStdString(d.title));
    }
    QStringList nameList = nameSet.values();
    QCompleter *completer = new QCompleter(nameList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    ui->searchbar->setCompleter(completer);

    ui->mainsort->setChecked(true);
    connect(button_grooup, &QButtonGroup::buttonClicked, this, &diarywindow::choose_sort_model);
    emit button_grooup->buttonClicked(button_grooup->checkedButton());
    qDebug() << "日记页面加载完成";
}

diarywindow::~diarywindow()
{
    delete ui;
    emit windowclose();
}

void diarywindow::on_refresh_clicked()
{
    this->diarys = read_data::getInstance().read_diary_data();
    this->diarylist = this->diarys;
    emit button_grooup->buttonClicked(button_grooup->checkedButton());
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


//sort
void diarywindow::choose_sort_model(){             //排序方法选择
    QString str =button_grooup->checkedButton()->text();
    int totalsize = diarylist.size();
    if(!str.compare("按热度排序")){
        diarylist = getTopK(this->diarylist, totalsize, [](const diary &a, const diary &b) {
            return a.popularity > b.popularity; // 按热度排序
        });
    }
    else if(!str.compare("按评分排序"))
    {
        diarylist = getTopK(this->diarylist, totalsize, [](const diary &a, const diary &b) {
            return a.score > b.score; // 按评分排序
        });
    }
    else {
        diarylist = getTopK(this->diarylist, totalsize, [](const diary &a, const diary &b) {
            return a.score*1000 + a.popularity > b.score*1000 + b.popularity;     //综合评分排序
        });
    }
    updatePagination();
}

void diarywindow::show_diary(std::vector<diary> diarys)             //日记列表初始化
{
    ui->diaryslist->clear();
    if(diarys.size() == 0){
        QListWidgetItem *item = new QListWidgetItem(ui->diaryslist);
        item->setText("无结果，请重新搜索");
        return;
    }
    // QVBoxLayout *layout = new QVBoxLayout(ui->diaryslist);
    for(diary d : diarys){
        std::ostringstream oss;

        // 设置输出格式
        oss << std::left; // 左对齐

        // 控制字段宽度，确保在每列有固定的宽度
        oss << std::setw(30) << d.title // 标题
            << std::setw(50) << ("景点: " + d.site_name) // 景点名称
            << std::setw(20) << ("作者: " + d.author_name) // 作者名称
            << std::setw(20) << ("热度: " + QString::number(d.popularity).toStdString()) // 热度
            << std::setw(20) << ("评分: " + QString::number(d.score, 'f', 1).toStdString()); // 评分（保留一位小数）
        QListWidgetItem *item = new QListWidgetItem(ui->diaryslist);
        item->setText(QString::fromStdString(oss.str()));
        item->setData(Qt::UserRole, QVariant::fromValue(d)); // 保存额外的信息
    }
}


//search
void diarywindow::on_sitesearch_clicked()
{
    this->diarylist = search_site(ui->searchbar->text().toStdString(), diarys, locations);
    emit button_grooup->buttonClicked(button_grooup->checkedButton());
}


void diarywindow::on_titlesearch_clicked()
{
    this->diarylist = search_title(ui->searchbar->text().toStdString(), diarys);
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

void diarywindow::on_load_local_diary_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        tr("选择文件"),           // 对话框标题
        QDir::homePath(),        // 默认起始目录
        tr("文本文件 (*.travel);;" // 文件过滤器
           "所有文件 (*)")
        );

    // 检查是否选择了文件
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "失败", "未选择文件");
        return;
    }
    else
        QMessageBox::information(this, "成功", "正在加载文件");
    // 读取文件内容
    HuffmanCoding h;
    diary d = h.load_diary(fileName);
    diaryread *dr = new diaryread(d);
    connect(this, &diarywindow::open_local_file, dr, &diaryread::local_diary_read);
    connect(dr, &diaryread::closewidget, this, &diarywindow::show);
    emit open_local_file();
    dr->show();
}

void diarywindow::closeEvent(QCloseEvent *event) {
    emit windowclose(); // 发出信号
}

bool diarywindow::eventFilter(QObject *obj, QEvent *event) {
    if (obj == ui->searchbar && event->type() == QEvent::FocusIn) {
        ui->searchbar->clear();
    }
    return QWidget::eventFilter(obj, event); // 保留默认行为
}


//page
void diarywindow::on_next_page_clicked()
{
    qDebug() << "点击下一页前 - 当前页:" << currentPage;

    int totalPages = getTotalPages();
    if (currentPage + 1 < totalPages) {
        currentPage++;
        qDebug() << "下一页有效跳转 - 新页码:" << currentPage;
        updatePagination(true);
    } else {
        qDebug() << "已是最后一页，无法继续下一页";
    }
}

void diarywindow::on_previous_page_clicked()
{
    qDebug() << "点击上一页前 - 当前页:" << currentPage;

    if (currentPage > 0) {
        currentPage--;
        qDebug() << "上一页有效跳转 - 新页码:" << currentPage;
        updatePagination(true);
    } else {
        qDebug() << "已是第一页，无法继续上一页";
    }
}

void diarywindow::updatePagination(bool keepPage)
{
    qDebug() << "---- 分页更新开始 ----";
    qDebug() << "当前数据总量:" << diarylist.size();
    qDebug() << "请求保持页码:" << keepPage;
    qDebug() << "当前页码(before):" << currentPage;

    // 计算总页数
    int totalPages = getTotalPages();
    qDebug() << totalPages << " " << diarylist.size();
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
    ui->previous_page->setEnabled(currentPage > 0);
    ui->next_page->setEnabled(currentPage < totalPages - 1);

    // 获取分页数据
    int startIdx = currentPage * itemsPerPage;
    int endIdx = std::min(startIdx + itemsPerPage, (int)diarylist.size());

    qDebug() << "分页范围:" << startIdx << "-" << endIdx;

    pagedDiarys.clear();
    if (startIdx < diarylist.size()) {
        pagedDiarys.assign(diarylist.begin() + startIdx,
                              diarylist.begin() + endIdx);
    }

    // 更新显示
    show_diary(pagedDiarys);
    ui->page_label->setText(
        QString("第 %1 页/共 %2 页 (共%3条)")
            .arg(currentPage + 1)
            .arg(totalPages)
            .arg(diarylist.size())
        );

    qDebug() << "---- 分页更新完成 ----\n";
}
