#include "diaryread.h"
#include "ui_diaryread.h"
#include "kmp_search.h"
#include <QMessageBox>
#include <QRegularExpression>

diaryread::diaryread(diary info, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::diaryread)
{
    info.popularity+=1;
    this->info = info;
    this->setWindowTitle("正在浏览日志");
    ui->setupUi(this);
    ui->context->setText(QString::fromStdString(info.context));
    ui->title->setText(QString::fromStdString(info.title));
    ui->author->setText("作者：" + QString::fromStdString(info.author_name));
    ui->score->setText("评分：" + QString::number(info.score));
    ui->popularity->setText("热度：" + QString::number(info.popularity));
    ui->site->setText("景点：" + QString::fromStdString(info.site_name));
    button_group = new QButtonGroup(this);
    button_group->addButton(ui->score1);
    button_group->addButton(ui->score2);
    button_group->addButton(ui->score3);
    button_group->addButton(ui->score4);
    button_group->addButton(ui->score5);
    // ui->context->setWordWrap
    ui->scrollArea->setWidgetResizable(true);
    QLabel *image = new QLabel();
    if(info.image_path.compare("0")){
        qDebug() << "图片输出" ;
        QPixmap px(QString::fromStdString(info.image_path)); 
        image->setPixmap(px.scaledToWidth(ui->scrollArea->viewport()->width(), Qt::SmoothTransformation)); // 调整图像宽度
    }
    else
        image->hide();
    QWidget *contentWidget = new QWidget();
    ui->scrolllayout->addWidget(ui->context);
    ui->scrolllayout->addWidget(image);
    contentWidget->setLayout(ui->scrolllayout);
    ui->scrollArea->setWidget(contentWidget);
}

diaryread::~diaryread()
{
    if(button_group->checkedButton() != nullptr)
        diary_score_change((button_group->checkedButton()->text()).toInt());
    diary_data_change();
    emit closewidget();
    delete ui;
}


void diaryread::diary_data_change()
{
    update_database ud(info);
    ud.change_data();
}

void diaryread::diary_score_change(int number)
{
    float ans = this->info.score_number * this->info.score;
    this->info.score_number++;
    ans += number;
    this->info.score = ans / this->info.score_number;
}

void diaryread::on_close_botton_clicked()
{
    diaryread::~diaryread();
}


void diaryread::on_searchbutton_clicked()
{
    QString str = ui->context_search->toPlainText();
    if(!KMP::kmpMatch(info.context, str.toStdString())){
        QMessageBox::warning(this, "失败", "没有搜索到对应内容");
        ui->context->setText(QString::fromStdString(info.context));
    }
    else {
        QString highlightedText = QString::fromStdString(info.context);
        QString replacement = "<span style='background-color: yellow;'>%1</span>";
        QRegularExpression regex(QRegularExpression::escape(str));
        highlightedText.replace(regex, replacement.arg(str));
        ui->context->setHtml(highlightedText); // 更新 QTextBrowser 的内容
    }
}


void diaryread::on_compress_donwload_clicked()
{
    HuffmanCoding h;
    int k = h.save_diary(info);
    if(k == 0){
        QMessageBox::warning(this, "失败", "保存失败");
    }
    else{
        QMessageBox::information(this, "成功", "保存成功");
    }
}

void diaryread::local_diary_read()
{
    this->setWindowTitle("正在浏览本地日志");
    ui->score->hide();
    ui->popularity->hide();
    ui->compress_donwload->hide();
    ui->score1->hide();
    ui->score2->hide();
    ui->score3->hide();
    ui->score4->hide();
    ui->score5->hide();
}
