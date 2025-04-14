#ifndef LOCATION_CHOOSE_H
#define LOCATION_CHOOSE_H

#include <QDialog>
#include <QComboBox>
#include <vector>
#include "simple_class/location.h"
namespace Ui {
class location_choose;
}

class location_choose : public QDialog
{
    Q_OBJECT

public:
    explicit location_choose(std::vector<location> locations, QWidget *parent = nullptr);
    ~location_choose();

signals:
    void location_pass(const QString &l);
private:
    Ui::location_choose *ui;
    std::vector<location> locations;
};

#endif // LOCATION_CHOOSE_H
