#ifndef OPTION_H
#define OPTION_H

#include <QtCore/QString>
#include <QtGui/QPixmap>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

#include "itemsid.h"
#include "option_selected.h"
#include "ui_option.h"

class Option : public QWidget {
  Q_OBJECT
 private:
  Ui::Option ui;
  size_t type;
  size_t id;
  QString name;
  QPixmap icon;
  OptionSelected* current_option;

 public:
  Option(QWidget* parent = nullptr, size_t type = 0, size_t id = 0,
         const QString& name = QString(), const QString& icon_path = QString(),
         OptionSelected* current_option = nullptr);
  ~Option();

  Option(const Option&) = delete;              // No copy constructor
  Option& operator=(const Option&) = delete;   // No copy constructor
  Option(Option&& other) = delete;             // No move constructor
  Option& operator=(Option&& other) = delete;  // No move constructor

  QPushButton* getButton();

 private slots:

  void on_OptionButton_clicked();
};

#endif  // OPTION_H
