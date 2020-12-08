#ifndef OPTION_H
#define OPTION_H

#include <QPushButton>
#include <QWidget>

#include "itemsid.h"
#include "option_selected.h"
#include "ui_option.h"

class Option : public QWidget {
  Q_OBJECT

 public:
  Option(QWidget* parent = nullptr, size_t id = 0,
         const QString& icon_path = QString(),
         OptionSelected* current_option = nullptr);
  ~Option();

  Option(const Option&) = delete;              // No copy constructor
  Option& operator=(const Option&) = delete;   // No copy constructor
  Option(Option&& other) = delete;             // No move constructor
  Option& operator=(Option&& other) = delete;  // No move constructor

  QPushButton* getButton();

 private slots:

  void on_OptionButton_clicked();

 private:
  Ui::Option ui;
  size_t id;
  OptionSelected* current_option;
};

#endif  // OPTION_H
