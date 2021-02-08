#include "object.h"

Object::Object(unsigned char res_id, double x_pos, double y_pos, double angle,
               int id)
    : res_id(res_id), position(x_pos, y_pos, angle), Identifiable(id) {}

Object::Object(unsigned char res_id, Point position, double angle, int id)
    : res_id(res_id), position(position, angle), Identifiable(id) {}

Object::Object(unsigned char res_id, Ray position, int id)
    : res_id(res_id), position(position), Identifiable(id) {}

Object::~Object() {}

unsigned char Object::get_res_id() { return res_id; }

Point Object::get_position() const { return position.get_origin(); }

double Object::get_angle() const { return position.get_angle(); }