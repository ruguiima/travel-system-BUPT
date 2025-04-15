#ifndef WRITEWIDGET_H
#define WRITEWIDGET_H

#include <QWidget>

namespace Ui {
class writewidget;
}

class writewidget : public QWidget
{
    Q_OBJECT

public:
    explicit writewidget(QWidget *parent = nullptr, QString site = nullptr);
    ~writewidget();

signals:
    void closewidget();
private slots:
    void on_close_clicked();

private:
    Ui::writewidget *ui;
    QString site;
};

#endif // WRITEWIDGET_H
