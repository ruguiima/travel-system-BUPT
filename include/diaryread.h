#ifndef DIARYREAD_H
#define DIARYREAD_H

#include <QWidget>
#include "simple_class/diary.h"
#include <QButtonGroup>
#include "tool_class/update_database.h"
#include "tool_class/HuffmanCoding.h"
#include <QPixmap>

namespace Ui {
class diaryread;
}

class diaryread : public QWidget
{
    Q_OBJECT

public:
    explicit diaryread(diary info, QWidget *parent = nullptr);
    void diary_data_change();
    void diary_score_change(int number);
    void closeEvent(QCloseEvent *event) override;
    ~diaryread();

signals:
    void closewidget();

public slots:
    void local_diary_read();

private slots:

    void on_searchbutton_clicked();

    void on_compress_donwload_clicked();

private:
    Ui::diaryread *ui;
    QButtonGroup *button_group;
    diary info;
};

#endif // DIARYREAD_H
