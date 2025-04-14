#ifndef DIARYREAD_H
#define DIARYREAD_H

#include <QWidget>
#include "./simple_class/diary.h"
#include <QButtonGroup>

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
    ~diaryread();

private:
    Ui::diaryread *ui;
    QButtonGroup *button_group;
    diary info;
};

#endif // DIARYREAD_H
