#include "vec.h"

#include <iostream>

Vector::Vector() {
    x.setNumber(0.0);
    y.setNumber(0.0);
}

Vector::Vector(Number x1, Number y1) {
    this->x.setNumber(x1.getNumber());
    this->y.setNumber(y1.getNumber());
}

Number Vector::calculatePolarRadius() {
    return Number(sqrt((x * x + y * y).getNumber()));
}

Number Vector::calculatePolarAngle() {
    return Number(atan((y / x).getNumber()));
}

Vector Vector::operator+(const Vector& vector) {
    return Vector(x + vector.x, y + vector.y);
}
