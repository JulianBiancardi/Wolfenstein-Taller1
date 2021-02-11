#include "../include/settings_view.h"

#include <QStackedWidget>

#include "moc_settings_view.cpp"

#define MATCHLIST_PAGE 0

SettingsView::SettingsView(QWidget* parent, Settings* settings)
    : QWidget(parent), settings(settings) {
  ui.setupUi(this);
  resolutions_buttongroup.addButton(ui.Resolution1);
  resolutions_buttongroup.addButton(ui.Resolution2);
  resolutions_buttongroup.addButton(ui.ResolutionFullScreen);
}

SettingsView::~SettingsView() {}

void SettingsView::on_Resolution1_clicked() {
  settings->set_resolution(320, 200, false);
}

void SettingsView::on_Resolution2_clicked() {
  settings->set_resolution(640, 400, false);
}

void SettingsView::on_ResolutionFullScreen_clicked() {
  settings->set_resolution(0, 0, true);
}

void SettingsView::on_ConfirmButton_clicked() {
  settings->set_music_volume(ui.MusicSlider->value());
  settings->set_effect_volume(ui.EffectsSlider->value());

  QStackedWidget* stacked_widget = (QStackedWidget*)this->parent();
  if (stacked_widget != nullptr) {
    stacked_widget->setCurrentIndex(MATCHLIST_PAGE);
  }
}
