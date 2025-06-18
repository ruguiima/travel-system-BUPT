#include "writewidget.h"
#include "ui_writewidget.h"

writewidget::writewidget(user u, QWidget *parent, QString site, int site_id)
    : QWidget(parent)
    , ui(new Ui::writewidget)
{
    ui->setupUi(this);
    this->setWindowTitle("日记编写");
    // setWindowFlags(Qt::FramelessWindowHint);
    this->u = u;
    this->site = site;
    this->d.site_id = site_id;
    this->d.image_path = "0";
    ui->location_title->setText(site);
}

writewidget::~writewidget()
{
    emit writewidget::closewidget();
    delete ui;
}

void writewidget::on_close_clicked()
{
    writewidget::~writewidget();
}



void writewidget::on_finisharticle_clicked()
{
    d.id = -1;
    d.author = u.id;
    d.context = ui->textEdit->toPlainText().toStdString();
    d.title = ui->title->toPlainText().toStdString();
    update_database ud(d);
    ud.change_data();
    writewidget::~writewidget();
}

void writewidget::on_uploadimage_clicked()
{
    // 打开文件对话框，让用户选择文件
    QString filePath = QFileDialog::getOpenFileName(this, "选择一张图片", "", "Images (*.png *.jpg *.jpeg *.bmp)");

    if (!filePath.isEmpty()) {
        // 定义存储图片的目标文件夹（相对路径）
        QString targetDir = "data/uploaded_images";
        QDir dir(targetDir);

        // 如果目录不存在则创建它
        if (!dir.exists()) {
            dir.mkpath(".");  // 创建文件夹
        }

        // 获取文件名称并构建目标路径
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        QString targetPath = dir.filePath(fileName);

        // 保存文件
        if (QFile::copy(filePath, targetPath)) {
            QString storedPath = targetPath; // 保存路径
            QMessageBox::information(this, "成功", "图片上传成功！\n存储路径: " + storedPath);
            qDebug() << "图片已保存到:" << storedPath;
            d.image_path = storedPath.toStdString();
        } else {
            QMessageBox::warning(this, "失败", "图片上传失败，请重试。");
        }
    }
}

