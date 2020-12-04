#include "mapgrid.h"
#include "ui_mapgrid.h"

#include "celd.h"

MapGrid::MapGrid(QWidget *parent,int rows, int columns,ItemsId* ids, OptionSelected* current_option) :
    QWidget(parent),
    ui(new Ui::MapGrid),
    rows(rows),
    columns(columns),
    current_option(current_option)
{
    ui->setupUi(this);
    generateCelds(ids,current_option);
}

MapGrid::~MapGrid()
{
    delete ui;
}


void MapGrid::generateCelds(ItemsId* ids, OptionSelected* current_option ){
    QGridLayout* gridlayout = new QGridLayout();
    gridlayout->setSpacing(0);
    for (int row = 0; row < rows;row++) {
        for (int colum = 0; colum < columns;colum++) {
            Celd* celd = new Celd(this,ids,current_option);
            gridlayout->addWidget(celd,row,colum);
        }
    }
    this->ui->scrollContent->setLayout(gridlayout);
}

void MapGrid::clear(){

}
