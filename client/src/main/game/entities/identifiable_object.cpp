#include "identifiable_object.h"

IdentifiableObject::IdentifiableObject(const Ray& position, int id)
    : Identifiable(id), Object(position) {}

IdentifiableObject::~IdentifiableObject() {}
