//
// Created by renana on 1/7/19.
//

#include "Point.h"

Point::Point(int x, int y) : x(x), y(y) {}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

bool Point::operator==(Point other) {
    return this->x == other.x && this->y == other.y;
}

string Point::to_string() {
    return "{" + to_string(x) + "," + to_string(y) + "}";
}