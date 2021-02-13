#include "identifiable_object.h"

IdentifiableObject::IdentifiableObject(const Ray& position,
                                       unsigned int resource_id,
                                       unsigned int id)
    : Identifiable(id), Object(position, resource_id) {}

IdentifiableObject::~IdentifiableObject() {}
