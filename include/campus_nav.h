#ifndef CAMPUS_NAV_H
#define CAMPUS_NAV_H

#include <QWidget>

namespace Ui {
class campus_nav;
}

class campus_nav : public QWidget
{
    Q_OBJECT

public:
    explicit campus_nav(QWidget *parent = nullptr);
    ~campus_nav();

signals:
    void windowclose();

private:
    Ui::campus_nav *ui;
};

#endif // CAMPUS_NAV_H
