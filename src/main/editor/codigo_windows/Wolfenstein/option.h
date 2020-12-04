#ifndef OPTION_H
#define OPTION_H

#include <QWidget>
#include <QPushButton>

#include "itemsid.h"
#include "optionselected.h"

namespace Ui {
class Option;
}

class Option : public QWidget
{
    Q_OBJECT

public:
     Option(QWidget *parent = nullptr,ssize_t id = -1, ItemsId* ids = nullptr, OptionSelected* current_option = nullptr);
    ~Option();

     QPushButton* getButton();

private slots:

     void on_OptionButton_clicked();

     void on_OptionButton_clicked(bool checked);

private:
    Ui::Option *ui;
    ssize_t id;
    OptionSelected* current_option;
};

#endif // OPTION_H
