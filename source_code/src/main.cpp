#include "mainwindow.h"
#include "login_widget.h"
#include "simple_class/user.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle(QStyleFactory::create("Fusion"));

    login_widget *login = new login_widget;
    login->show();

    QObject::connect(login, &login_widget::loginSucceeded, [&a, login](const user u) {
        MainWindow *w = new MainWindow(u);
        w->show();
        login->close();
    });

    return a.exec();
}

