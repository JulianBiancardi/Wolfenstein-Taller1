#include "option_selected.h"

#define BASE_ID 0

OptionSelected::OptionSelected() : current_id(BASE_ID), current_name("") {}

size_t OptionSelected::get_current_id() const { return current_id; }

QString OptionSelected::get_current_name() const { return current_name; }

QPixmap OptionSelected::get_current_icon() const { return current_icon; }

void OptionSelected::set_current_id(size_t value) {
  current_id = value;
  notify();
}

void OptionSelected::set_info(size_t id, const QString& name,
                              const QPixmap& icon) {
  current_id = id;
  current_name = name;
  current_icon = icon;
  notify();
}

OptionSelected::~OptionSelected() {}