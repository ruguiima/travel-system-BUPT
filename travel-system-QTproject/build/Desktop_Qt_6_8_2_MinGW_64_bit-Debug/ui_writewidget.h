/********************************************************************************
** Form generated from reading UI file 'writewidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WRITEWIDGET_H
#define UI_WRITEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_writewidget
{
public:
    QTextEdit *title;
    QTextEdit *textEdit;
    QLabel *biaoti;
    QPushButton *close;
    QPushButton *uploadimage;
    QPushButton *finisharticle;

    void setupUi(QWidget *writewidget)
    {
        if (writewidget->objectName().isEmpty())
            writewidget->setObjectName("writewidget");
        writewidget->resize(702, 392);
        title = new QTextEdit(writewidget);
        title->setObjectName("title");
        title->setGeometry(QRect(90, 10, 411, 41));
        textEdit = new QTextEdit(writewidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(10, 60, 491, 311));
        biaoti = new QLabel(writewidget);
        biaoti->setObjectName("biaoti");
        biaoti->setGeometry(QRect(20, 20, 66, 18));
        close = new QPushButton(writewidget);
        close->setObjectName("close");
        close->setGeometry(QRect(630, 20, 51, 31));
        uploadimage = new QPushButton(writewidget);
        uploadimage->setObjectName("uploadimage");
        uploadimage->setGeometry(QRect(560, 190, 81, 81));
        finisharticle = new QPushButton(writewidget);
        finisharticle->setObjectName("finisharticle");
        finisharticle->setGeometry(QRect(540, 20, 61, 31));

        retranslateUi(writewidget);

        QMetaObject::connectSlotsByName(writewidget);
    } // setupUi

    void retranslateUi(QWidget *writewidget)
    {
        writewidget->setWindowTitle(QCoreApplication::translate("writewidget", "Form", nullptr));
        biaoti->setText(QCoreApplication::translate("writewidget", "\346\240\207\351\242\230", nullptr));
        close->setText(QCoreApplication::translate("writewidget", "\345\205\263\351\227\255", nullptr));
        uploadimage->setText(QCoreApplication::translate("writewidget", "\345\233\276\347\211\207\344\270\212\344\274\240", nullptr));
        finisharticle->setText(QCoreApplication::translate("writewidget", "\345\256\214\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class writewidget: public Ui_writewidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WRITEWIDGET_H
