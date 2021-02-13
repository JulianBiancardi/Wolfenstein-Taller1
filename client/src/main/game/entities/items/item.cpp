#include "item.h"

Item::Item(const Ray& position, unsigned int resource_id, unsigned int id)
    : IdentifiableObject(position, resource_id, id) {}

Item::~Item() {}
