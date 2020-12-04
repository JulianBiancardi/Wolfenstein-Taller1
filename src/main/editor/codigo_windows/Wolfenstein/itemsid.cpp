#include "itemsid.h"

ItemsId::ItemsId(){

    ids.insert(0,":/images/IMG_Pistol.png");
    ids.insert(1,":/images/IMG_Bazooka.png");
    ids.insert(2,":/images/IMG_Key.png");
    ids.insert(3,":/images/IMG_Machingun.png");
    ids.insert(4,":/images/IMG_StoneWall.png");
    ids.insert(5,":/images/IMG_Guard.png");
    ids.insert(6,":/images/IMG_Treasure_Cup.png");
    ids.insert(7,":/images/IMG_Treasure_Crown.png");
    ids.insert(8,":/images/IMG_Treasure_Chest.png");
    ids.insert(9,":/images/IMG_Food.png");
    ids.insert(10,":/images/IMG_WoodWall.png");
    ids.insert(11,":/images/IMG_RockWall.png");
    ids.insert(12,":/images/IMG_MedKit.png");
}

const QString ItemsId::getImagePath(int id) const{
    return ids.value(id);
}
