#include "itemsid.h"

ItemsId::ItemsId() {
  ids.insert(0, "resources/images/IMG_Pistol.png");
  ids.insert(1, "resources/images/IMG_Bazooka.png");
  ids.insert(2, "resources/images/IMG_Key.png");
  ids.insert(3, "resources/images/IMG_Machingun.png");
  ids.insert(4, "resources/images/IMG_StoneWall.png");
  ids.insert(5, "resources/images/IMG_Guard.png");
  ids.insert(6, "resources/images/IMG_Treasure_Cup.png");
  ids.insert(7, "resources/images/IMG_Treasure_Crown.png");
  ids.insert(8, "resources/images/IMG_Treasure_Chest.png");
  ids.insert(9, "resources/images/IMG_Food.png");
  ids.insert(10, "resources/images/IMG_WoodWall.png");
  ids.insert(11, "resources/images/IMG_RockWall.png");
  ids.insert(12, "resources/images/IMG_MedKit.png");
}

const QString ItemsId::getImagePath(int id) const { return ids.value(id); }
