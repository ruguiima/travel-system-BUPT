#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "diarywindow.h"
#include "campus_nav.h"
#include "simple_class/user.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(user u, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_diary_widget_clicked();

    void on_roadwidget_clicked();

private:
    Ui::MainWindow *ui;
    user u;
    diarywindow *diary_window;
    campus_nav *cam;
};
#endif // MAINWINDOW_H
