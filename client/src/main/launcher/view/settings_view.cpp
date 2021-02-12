#include "../include/settings_view.h"

#include <QStackedWidget>
#include <iostream>  //TODO DELETE
#include <sstream>
#include <string>

#include "moc_settings_view.cpp"

#define MATCHLIST_PAGE 0
#define CHAR_X 'x'
SettingsView::SettingsView(QWidget* parent, Settings* settings)
    : QWidget(parent), settings(settings) {
  ui.setupUi(this);
}

SettingsView::~SettingsView() {}

void SettingsView::on_ConfirmButton_clicked() {
  size_t width;
  size_t height;
  bool fullscreen = ui.FullscreenCheckBox->isChecked();

  std::string resolution = ui.ResolutionBox->currentText().toStdString();
  size_t pos = resolution.find_first_of(CHAR_X, 0);
  if (pos != std::string::npos) {
    std::stringstream widthss(resolution.substr(0, pos));
    std::stringstream heightss(
        resolution.substr(pos + 1, resolution.length() - pos));
    widthss >> width;
    heightss >> height;
  }

  settings->set_resolution(width, height, fullscreen);
  settings->set_music_volume(ui.MusicSlider->value());
  settings->set_effect_volume(ui.EffectsSlider->value());

  QStackedWidget* stacked_widget = (QStackedWidget*)this->parent();
  if (stacked_widget != nullptr) {
    stacked_widget->setCurrentIndex(MATCHLIST_PAGE);
  }
}
