#include "celd.h"
#include "ui_celd.h"
#include "mapgrid.h"
#include "iostream"

Celd::Celd(QWidget *parent,ItemsId* ids, OptionSelected* current_option) :
    QWidget(parent),
    ui(new Ui::Celd),
    ids(ids),
    current_option(current_option)
{
    ui->setupUi(this);
}

Celd::~Celd(){
    delete ui;
}

QPushButton* Celd::getButton(){
    return this->ui->CeldButton;
}

void Celd::on_CeldButton_clicked(){
    //Update celd
    QPixmap pixmap(ids->getImagePath(current_option->getCurrent_id()));
    QIcon CeldIcon(pixmap);
    this->ui->CeldButton->setIcon(CeldIcon);
    this->ui->CeldButton->setIconSize(pixmap.rect().size());
}

void Celd::on_CeldButton_pressed(){
    std::cout << "Cel pressed" << std::endl;

}
