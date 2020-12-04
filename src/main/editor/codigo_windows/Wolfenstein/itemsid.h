#ifndef ITEMSID_H
#define ITEMSID_H

#include <QMap>
#include <QString>

class ItemsId
{
public:
    ItemsId();

    const QString getImagePath(int id) const;

private:
    QMap<int,QString> ids;
};

#endif // ITEMSID_H
