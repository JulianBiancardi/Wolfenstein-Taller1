#include "identifiable_object.h"

IdentifiableObject::IdentifiableObject(unsigned char res_id, double x_pos,
                                       double y_pos, double angle, int id)
    : Identifiable(id), Object(res_id, Ray(x_pos, y_pos, angle)) {}

IdentifiableObject::IdentifiableObject(unsigned char res_id, Point position,
                                       double angle, int id)
    : Identifiable(id), Object(res_id, Ray(position, angle)) {}

IdentifiableObject::IdentifiableObject(unsigned char res_id, Ray position,
                                       int id)
    : Identifiable(id), Object(res_id, position) {}

IdentifiableObject::~IdentifiableObject() {}

void IdentifiableObject::domr() { position; }