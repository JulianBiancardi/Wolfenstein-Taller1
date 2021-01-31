#ifndef ITEMSID_H
#define ITEMSID_H

#include <QtCore/QMap>
#include <QtCore/QString>

class ItemsId {
 public:
  ItemsId();

  size_t size() const;
  size_t get_type(size_t id) const;
  const QString get_tooltip(size_t id) const;
  const QString get_icon_path(size_t id) const;
  const QMap<size_t, QMap<QString, QString>>& get_ids() const;

 private:
  QMap<size_t, QMap<QString, QString>> ids;
};

#endif  // ITEMSID_H
