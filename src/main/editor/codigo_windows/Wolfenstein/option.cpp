#include "option.h"
#include "ui_option.h"
#include "iostream"

//#define INVALID_ID -1

Option::Option(QWidget *parent, ssize_t id, ItemsId* ids,OptionSelected* current_option) :
    QWidget(parent),
    ui(new Ui::Option),
    id(id),
    current_option(current_option)
{
    if(this->id == -1){
        //TODO exception
    }
    ui->setupUi(this);
    QPixmap pixmap(ids->getImagePath(id));
    QIcon ButtonIcon(pixmap);
    this->ui->OptionButton->setIcon(ButtonIcon);
}

Option::~Option(){
    delete ui;
}


QPushButton* Option::getButton(){
    return this->ui->OptionButton;
}


void Option::on_OptionButton_clicked(){
     current_option->setCurrent_id(this->id);
}

void Option::on_OptionButton_clicked(bool checked){
    std::cout << checked << std::endl;
}
