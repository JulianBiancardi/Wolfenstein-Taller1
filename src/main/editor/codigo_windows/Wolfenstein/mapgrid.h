#ifndef MAPGRID_H
#define MAPGRID_H

#include <QWidget>
#include <QButtonGroup>

#include "itemsid.h"
#include "optionselected.h"

namespace Ui {
class MapGrid;
}

class MapGrid : public QWidget
{
    Q_OBJECT

public:
     MapGrid(QWidget *parent = nullptr, int rows = 50, int columns = 50,ItemsId* ids = nullptr ,OptionSelected* current_option = nullptr);
    ~MapGrid();

     void clear();

private:
    Ui::MapGrid *ui;
    int rows;
    int columns;
    OptionSelected* current_option;

    void generateCelds(ItemsId* ids, OptionSelected* current_option);
};

#endif // MAPGRID_H
