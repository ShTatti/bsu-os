#ifndef VEC_VEC_H
#define VEC_VEC_H

#include "../num/library.h"
#include "cmath"

class Vector {
        private:
        Number x;
        Number y;

        public:
        Vector();
        Vector(Number x, Number y);
        Number calculatePolarRadius();
        Number calculatePolarAngle();
        Vector operator+(const Vector& vector);
};

const Vector VECTOR_ZERO = Vector(Number(0), Number(0));
const Vector VECTOR_ONE = Vector(Number(1), Number(1));

#endif //VEC_VEC_H
