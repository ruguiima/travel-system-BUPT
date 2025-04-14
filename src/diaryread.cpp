#include "diaryread.h"
#include "ui_diaryread.h"

diaryread::diaryread(diary info, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::diaryread)
{
    info.popularity+=1;
    this->info = info;
    ui->setupUi(this);
    ui->context->setText(QString::fromStdString(info.context));
    ui->title->setText(QString::fromStdString(info.title));
    ui->author->setText("作者：" + QString::fromStdString(info.author_name));
    ui->score->setText("评分：" + QString::number(info.score));
    ui->popularity->setText("热度：" + QString::number(info.popularity));
    ui->site->setText("景点：" + QString::number(info.site_id));
    button_group = new QButtonGroup(this);
    button_group->addButton(ui->score1);
    button_group->addButton(ui->score2);
    button_group->addButton(ui->score3);
    button_group->addButton(ui->score4);
    button_group->addButton(ui->score5);
}

diaryread::~diaryread()
{
    diary_score_change((button_group->checkedButton()->text()).toInt());
    diary_data_change();
    delete ui;
}

void diaryread::diary_data_change()
{

}

void diaryread::diary_score_change(int number)
{
    float ans = this->info.score_number * this->info.score;
    this->info.score_number++;
    ans += number;
    this->info.score = ans / this->info.score_number;
}
