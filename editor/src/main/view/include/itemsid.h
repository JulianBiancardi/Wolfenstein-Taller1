#ifndef ITEMSID_H
#define ITEMSID_H

#include <QtCore/QMap>
#include <QtCore/QString>

class ItemsId {
 public:
  ItemsId();

  const QString get_icon_path(size_t id) const;

 private:
  QMap<size_t, QString> ids;
};

#endif  // ITEMSID_H
