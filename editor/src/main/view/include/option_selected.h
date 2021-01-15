#ifndef OPTION_SELECTED_H
#define OPTION_SELECTED_H

#include <Iobservable.h>
#include <sys/types.h>

#include <QtCore/QString>
#include <QtGui/QPixmap>

class OptionSelected : public IObservable {
 private:
  size_t current_id;
  QString current_name;
  QPixmap current_icon;
  int current_state;

 public:
  OptionSelected();

  size_t get_current_id() const;
  QString get_current_name() const;
  QPixmap get_current_icon() const;
  int state() const;

  void change_state(int new_state);
  void set_info(size_t id, const QString& name, const QPixmap& icon);

  ~OptionSelected();
};

#endif  // OPTION_SELECTED_H