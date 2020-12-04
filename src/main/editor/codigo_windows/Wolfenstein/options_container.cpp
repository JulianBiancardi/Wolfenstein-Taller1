#include "options_container.h"
#include "ui_options_container.h"
#include "option.h"
#include "iostream"

OptionsContainer::OptionsContainer(QWidget *parent,const int rows, const int columns,ItemsId* ids, OptionSelected* current_option) :
    QWidget(parent),
    ui(new Ui::Options),
    rows(rows),
    columns(columns),
    buttongroup(this)
{
    ui->setupUi(this);
    addOptions(ids,current_option);

    /*
    this->buttongroup.connect(buttongroup, static_cast<void(QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),[=](QAbstractButton *button){
        //seleccionado = boton.value
        //
    });*/
}

OptionsContainer::~OptionsContainer(){
    delete ui;
}


void OptionsContainer::addOptions(ItemsId* ids, OptionSelected* current_option){
    QList<int> ids_section;
    ids_section.append(0);
    ids_section.append(2);
    ids_section.append(5);
    ids_section.append(1);
    ids_section.append(8);
    ids_section.append(6);
    ids_section.append(4);
    ids_section.append(7);
    ids_section.append(10);
    ids_section.append(11);
    ids_section.append(9);
    ids_section.append(12);

    QGridLayout* gridlayout = new QGridLayout();
    gridlayout->setSpacing(5);
    for (int i = 0; i < ids_section.size() ; i++) {
        Option* option = new Option(this,ids_section.at(i),ids,current_option);
        int row = i / this->columns;
        int column = i % this->columns;
        gridlayout->addWidget(option,row,column);
        this->buttongroup.addButton(option->getButton());
    }
    this->ui->scrollAreaWidgetContents->setLayout(gridlayout);
}



