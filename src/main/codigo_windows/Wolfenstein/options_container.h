#ifndef OPTIONS_CONTAINER_H
#define OPTIONS_CONTAINER_H

#include <QWidget>
#include "option.h"
#include "QButtonGroup"

#include "itemsid.h"
#include "optionselected.h"
//------------------------------------------------------------------
namespace Ui {
class Options;
}

class OptionsContainer : public QWidget
{
    Q_OBJECT

public:
     OptionsContainer(QWidget *parent = nullptr,const int rows = 3, const int columns = 5, ItemsId* ids = nullptr, OptionSelected* current_option = nullptr);
    ~OptionsContainer();

private:
    Ui::Options *ui;
    int rows;
    int columns;
    QButtonGroup buttongroup;

    void addOptions(ItemsId* ids, OptionSelected* current_option);
};

#endif // OPTIONS_CONTAINER_H
//------------------------------------------------------------------
