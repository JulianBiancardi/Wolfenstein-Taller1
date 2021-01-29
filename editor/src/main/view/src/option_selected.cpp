#include "option_selected.h"

#define BASE_TYPE 0
#define BASE_ID 0
#define EDIT_STATE 1
#define DRAG_STATE 2
#define CLEAR_STATE 3

OptionSelected::OptionSelected()
    : current_type(BASE_TYPE),
      current_id(BASE_ID),
      current_name(""),
      current_state(EDIT_STATE) {}

size_t OptionSelected::get_current_type() const { return current_type; }

size_t OptionSelected::get_current_id() const { return current_id; }

QString OptionSelected::get_current_name() const { return current_name; }

QPixmap OptionSelected::get_current_icon() const { return current_icon; }

int OptionSelected::state() const { return current_state; }

void OptionSelected::change_state(int new_state) { current_state = new_state; }

void OptionSelected::set_info(size_t type, size_t id, const QString& name,
                              const QPixmap& icon) {
  current_type = type;
  current_id = id;
  current_name = name;
  current_icon = icon;
  notify();
}

OptionSelected::~OptionSelected() {}