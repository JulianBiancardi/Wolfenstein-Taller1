#ifndef ITEMSID_H
#define ITEMSID_H

#include <QtCore/QMap>
#include <QtCore/QString>

class ItemsId {
 public:
  ItemsId();

  size_t size() const;
  const QString get_tooltip(size_t id) const;
  const QString get_icon_path(size_t id) const;

 private:
  QMap<size_t, QMap<QString, QString>> ids;
};

#endif  // ITEMSID_H
