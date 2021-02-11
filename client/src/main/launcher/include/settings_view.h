#ifndef SETTINGS_VIEW_H
#define SETTINGS_VIEW_H

#include <QtWidgets/QWidget>

#include "../include/settings.h"
#include "ui_settings_view.h"

class SettingsView : public QWidget {
  Q_OBJECT

 private:
  Ui::SettingsView ui;
  Settings* settings;
  QButtonGroup resolutions_buttongroup;

 public:
  SettingsView(QWidget* parent = nullptr, Settings* settings = nullptr);

  ~SettingsView();

 private slots:
  void on_Resolution1_clicked();
  void on_Resolution2_clicked();
  void on_ResolutionFullScreen_clicked();
  void on_ConfirmButton_clicked();
};
#endif  // SETTINGS_VIEW_H