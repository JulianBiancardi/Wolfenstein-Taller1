#include "rectangle.h"

Rectangle::Rectangle(size_t top, size_t bot, size_t left, size_t right)
    : left(left), right(right), top(top), bot(bot) {}

Rectangle::~Rectangle() {}

size_t Rectangle::get_left() { return left; }
size_t Rectangle::get_right() { return right; }
size_t Rectangle::get_top() { return top; }
size_t Rectangle::get_bot() { return bot; }
size_t Rectangle::get_width() { return right - left; }
size_t Rectangle::get_height() { return bot - top; }
