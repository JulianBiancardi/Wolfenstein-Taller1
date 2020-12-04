#ifndef CELD_H
#define CELD_H

#include <QWidget>
#include <QPushButton>

#include "itemsid.h"
#include "optionselected.h"

namespace Ui {
class Celd;
}

class Celd : public QWidget
{
    Q_OBJECT

public:
    explicit Celd(QWidget *parent = nullptr,ItemsId* ids = nullptr, OptionSelected* current_option = nullptr);
    ~Celd();

    QPushButton* getButton();

private slots:
    void on_CeldButton_clicked();

    void on_CeldButton_pressed();

private:
    Ui::Celd *ui;
    ItemsId* ids;
    OptionSelected* current_option;
};

#endif // CELD_H
