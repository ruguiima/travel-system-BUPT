#include "location_choose.h"
#include "ui_location_choose.h"

location_choose::location_choose(std::vector<location> locations, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::location_choose)
{
    this->locations = locations;
    ui->setupUi(this);
    for(location l : locations)
        ui->location_choose_box->addItem(QString::fromStdString(l.title));

    connect(ui->buttonBox, &QDialogButtonBox::accepted, [=]() {
        // 获取选中的参数并传递给主窗口
        emit location_pass(ui->location_choose_box->currentText());
        accept();
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    setWindowTitle("选择要写旅游日记的景点");
    });
}

location_choose::~location_choose()
{
    delete ui;
}
