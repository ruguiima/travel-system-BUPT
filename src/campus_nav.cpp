#include "campus_nav.h"
#include "ui_campus_nav.h"
#include <QCompleter>
#include <vector>
#include "top_k_algorithm.h"
#include <QMessageBox>
#include <QPainter>

campus_nav::campus_nav(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::campus_nav)
{
    ui->setupUi(this);

    // Load the data from a JSON file
    QString filename = ":/json/data/map_of_bupt.geojson";
    rp.load(filename);
    qDebug() << "Loaded map data success.";

    QStringList nameList;
    for (size_t i = 0; i < rp.places.size(); ++i) {
        nameList.append(rp.places[i].getName());
        place_name_to_id[rp.places[i].getName()] = i; // Store the mapping from name to ID
    }
    QCompleter *completer = new QCompleter(nameList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    ui->lineEdit_start->setCompleter(completer);
    ui->lineEdit_end->setCompleter(completer);
    this->setWindowTitle("校园导航");

    rp.create_graph();
    qDebug() << "Created graph success.";

}

campus_nav::~campus_nav()
{
    delete ui;
    emit windowclose();
}

void campus_nav::on_pushButton_cur_clicked()
{

    if(place_name_to_id.find(ui->lineEdit_start->text()) != place_name_to_id.end()){
        cur_loc = place_name_to_id[ui->lineEdit_start->text()];

        currentDrawMode = None;
        update();

        QMessageBox::information(this, "", "位置更新成功");
    } else{
        QMessageBox::warning(this, "", "未找到该位置，请检查输入是否正确");
    }
}


void campus_nav::on_pushButton_search_clicked()
{
    std::vector<place> nearby;
    if (cur_loc == -1) {
        qDebug() << "Please select a current location first.";
        return;
    }
    for(place& p : rp.places){
        p.dist = calcu_length(rp.places[cur_loc].getLoct(), p.getLoct());
    }
    nearby = getTopK(rp.places, 80, [](const place &a, const place &b) {
        return a.dist < b.dist;// Sort by distance
    });
    std::vector<place> result;
    for (const place& p : nearby) {
        if(p.dist > ui->doubleSpinBox->value()) break;
        if(p.dist == 0) continue;
        if (ui->comboBox_placeType->currentText() == "选择场所类型" || p.getType() == ui->comboBox_placeType->currentText()) {
            result.push_back(p);
        }
    }
    show_nearby(result);
    placesToDraw = result;
    currentDrawMode = DrawPlaces;
    update();
}

void campus_nav::show_nearby(std::vector<place> result)
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->textEdit_nearby->clear();
    ui->textEdit_nearby->append("附近场所：");
    if (result.empty()) {
        qDebug() << "No nearby places found.";
        ui->textEdit_nearby->append("没有找到附近的场所。");
    }
    for (const place& p : result) {
        ui->textEdit_nearby->append(p.getName() + "    距离：" + QString::number(p.dist) + "m");
    }
}


void campus_nav::on_pushButton_dest_clicked()
{
    if(place_name_to_id.find(ui->lineEdit_end->text()) == place_name_to_id.end()){
        QMessageBox::warning(this, "", "未找到该位置，请检查输入是否正确");
        return;
    }
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    // 添加名称项
    QTableWidgetItem* item = new QTableWidgetItem(ui->lineEdit_end->text());
    ui->tableWidget->setItem(row, 0, item);

    // 添加删除按钮
    QPushButton* delBtn = new QPushButton("删除");
    ui->tableWidget->setCellWidget(row, 1, delBtn);

    // 绑定按钮点击信号到槽函数
    connect(delBtn, &QPushButton::clicked, this, &campus_nav::onDeleteButtonClicked);
}

// 槽函数：删除该按钮所在行
void campus_nav::onDeleteButtonClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    // 遍历找到该按钮所在的行
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        if (ui->tableWidget->cellWidget(row, 1) == button) {
            ui->tableWidget->removeRow(row);
            break;
        }
    }
}

void campus_nav::on_pushButton_plan_clicked()
{
    std::vector<int> dest_id;
    int rowCount = ui->tableWidget->rowCount();
    for(int row = 0; row < rowCount; row++){
        QString text = ui->tableWidget->item(row, 0)->text();
        if(place_name_to_id.find(text) != place_name_to_id.end()) {
            dest_id.push_back(place_name_to_id[text]);
        } else {
            qDebug() << "Place not found: " << text;
        }
    }

    ui->stackedWidget->setCurrentIndex(1);
    ui->textEdit_route->clear();
    std::vector<place_info> record;

    QString strategy = ui->comboBox_strategy->currentText();
    double dist;
    if(strategy == "距离最短"){
        dist = route_plan::shortest_path(cur_loc, dest_id, rp.graph_d, record);
        ui->textEdit_route->append("最短距离:" + QString::number(dist) + "m");
        ui->textEdit_route->append("路径详情：");
        for (const auto &p : record){
            ui->textEdit_route->append("下一途径点：" + rp.places[p.getId()].getName() + " 总路程："
                                       + QString::number(p.getWeight()) + "m");
        }
    }
    else if(strategy == "步行时间最短"){
        dist = route_plan::shortest_path(cur_loc, dest_id, rp.graph_t, record);
        ui->textEdit_route->append("最短用时:" + QString::number(dist) + "s");
        ui->textEdit_route->append("路径详情：");
        for (const auto &p : record){
            ui->textEdit_route->append("下一途径点：" + rp.places[p.getId()].getName() + " 共用时："
                                       + QString::number(p.getWeight()) + "s");
        }
    }
    else if(strategy == "混合交通工具时间最短"){
        dist = route_plan::shortest_path(cur_loc, dest_id, rp.graph_m, record);
        ui->textEdit_route->append("最短用时:" + QString::number(dist) + "s");
        ui->textEdit_route->append("路径详情：");
        for (const auto &p : record){
            ui->textEdit_route->append("下一途径点：" + rp.places[p.getId()].getName() + " 共用时："
                                       + QString::number(p.getWeight()) + "s 方式："
                                        + (p.getType() == cycleway ? "自行车道" : "人行道") );
        }
    } else {
        qDebug() << "Unknown strategy: " << strategy;
        return;
    }

    placesToDraw.clear();
    for (const auto &id : dest_id) {
        placesToDraw.push_back(rp.places[id]);
    }
    routeToDraw = record;
    currentDrawMode = DrawRoute;
    update();
}


void campus_nav::on_pushButton_nearby_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void campus_nav::on_pushButton_route_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void campus_nav::closeEvent(QCloseEvent *event) {
    emit windowclose(); // 发出信号
}

void campus_nav::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event); // 保证其他控件正常绘制
    QPainter painter(this);

    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.setRenderHint(QPainter::Antialiasing);

    QImage mapImage(":/images/data/map.png");
    QRect targetRect(29, 151, 400, 586);
    painter.drawImage(targetRect, mapImage);

    if (currentDrawMode == DrawRoute) {
        painter.setPen(QPen(Qt::blue, 3));
        for (size_t i = 0; i < routeToDraw.size(); ++i) {
            if(routeToDraw[i].getType() == cycleway){
                painter.setPen(QPen(Qt::green, 3)); // 自行车道用蓝色
            } else {
                painter.setPen(QPen(Qt::blue, 3)); // 人行道用绿色
            }

            coor tar1 = i == 0 ? rp.places[cur_loc].getLoct() : rp.places[routeToDraw[i - 1].getId()].getLoct();
            coor tar2 = rp.places[routeToDraw[i].getId()].getLoct();
            QPointF p1 = mapCoordToPixel(tar1, targetRect);
            QPointF p2 = mapCoordToPixel(tar2, targetRect);
            painter.drawLine(p1, p2);
        }
    }

    if (currentDrawMode == DrawPlaces || currentDrawMode == DrawRoute) {
        painter.setBrush(Qt::darkRed);
        painter.setPen(Qt::black);

        for (const auto& p : placesToDraw) {
            QPointF pos = mapCoordToPixel(p.getLoct(), targetRect);
            painter.drawEllipse(pos, 3, 3);  // 半径为3的圆点
        }
    }

    QPixmap icon(":/images/data/icon.png");  // 替换成你的图标路径
    QPointF pos = mapCoordToPixel(rp.places[cur_loc].getLoct(), targetRect);

    QSize iconSize(24, 24);  // 自定义图标的绘制尺寸
    QPointF topLeft(pos.x() - iconSize.width() / 2.0, pos.y() - iconSize.height() / 2.0);

    QRectF iconRect(topLeft, iconSize);
    painter.drawPixmap(iconRect.toRect(), icon);  // 绘制
}


QPointF campus_nav::mapCoordToPixel(coor tar, QRect r)
{
    const double north = 39.96499;
    const double south = 39.95806;
    const double west = 116.35501;
    const double east = 116.36123;

    double normX = (tar.first - west) / (east - west);
    double normY = (tar.second - north) / (south - north);

    double pixelX = r.left() + normX * r.width();
    double pixelY = r.top() + normY * r.height();

    return QPointF(pixelX, pixelY);
}
