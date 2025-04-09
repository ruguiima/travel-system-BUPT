/********************************************************************************
** Form generated from reading UI file 'diarywindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIARYWINDOW_H
#define UI_DIARYWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_diarywindow
{
public:
    QTextEdit *searchbar;
    QPushButton *sitesearch;
    QPushButton *titlesearch;
    QCheckBox *popularityorder;
    QCheckBox *scoreorder;
    QPushButton *writediary;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *laout;

    void setupUi(QWidget *diarywindow)
    {
        if (diarywindow->objectName().isEmpty())
            diarywindow->setObjectName("diarywindow");
        diarywindow->resize(804, 447);
        searchbar = new QTextEdit(diarywindow);
        searchbar->setObjectName("searchbar");
        searchbar->setGeometry(QRect(10, 10, 481, 31));
        sitesearch = new QPushButton(diarywindow);
        sitesearch->setObjectName("sitesearch");
        sitesearch->setGeometry(QRect(530, 10, 88, 26));
        titlesearch = new QPushButton(diarywindow);
        titlesearch->setObjectName("titlesearch");
        titlesearch->setGeometry(QRect(670, 10, 88, 26));
        popularityorder = new QCheckBox(diarywindow);
        popularityorder->setObjectName("popularityorder");
        popularityorder->setGeometry(QRect(20, 60, 101, 24));
        scoreorder = new QCheckBox(diarywindow);
        scoreorder->setObjectName("scoreorder");
        scoreorder->setGeometry(QRect(20, 90, 101, 24));
        writediary = new QPushButton(diarywindow);
        writediary->setObjectName("writediary");
        writediary->setGeometry(QRect(0, 260, 111, 101));
        verticalLayoutWidget = new QWidget(diarywindow);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(160, 60, 631, 381));
        laout = new QVBoxLayout(verticalLayoutWidget);
        laout->setObjectName("laout");
        laout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(diarywindow);

        QMetaObject::connectSlotsByName(diarywindow);
    } // setupUi

    void retranslateUi(QWidget *diarywindow)
    {
        diarywindow->setWindowTitle(QCoreApplication::translate("diarywindow", "Form", nullptr));
        sitesearch->setText(QCoreApplication::translate("diarywindow", "\346\214\211\346\231\257\347\202\271\346\220\234\347\264\242", nullptr));
        titlesearch->setText(QCoreApplication::translate("diarywindow", "\346\214\211\345\220\215\347\247\260\346\220\234\347\264\242", nullptr));
        popularityorder->setText(QCoreApplication::translate("diarywindow", "\346\214\211\347\203\255\345\272\246\346\216\222\345\272\217", nullptr));
        scoreorder->setText(QCoreApplication::translate("diarywindow", "\346\214\211\350\257\204\345\210\206\346\216\222\345\272\217", nullptr));
        writediary->setText(QCoreApplication::translate("diarywindow", "\345\206\231\346\227\245\350\256\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class diarywindow: public Ui_diarywindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIARYWINDOW_H
