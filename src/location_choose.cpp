#include "location_choose.h"
#include "ui_location_choose.h"

location_choose::location_choose(std::vector<location> locations, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::location_choose)
{
    this->locations = locations;
    ui->setupUi(this);
    for(location l : locations){
        ui->location_choose_box->addItem(QString::number(l.id) + " "+ QString::fromStdString(l.title));
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, [=]() {
        // 获取选中的参数并传递给主窗口
        int kong = 0;
        QString str = ui->location_choose_box->currentText();
        kong = str.indexOf(" ");
        emit location_pass(str.mid(kong+1), str.mid(0,kong).toInt());
        accept();
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    setWindowTitle("选择要写旅游日记的景点");
    });
}

location_choose::~location_choose()
{
    delete ui;
}
