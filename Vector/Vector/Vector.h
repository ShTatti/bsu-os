#pragma once
#include "Number.h"

#ifdef VECTOR_EXPORTS
#define VECTOR_API __declspec(dllexport)
#else
#define VECTOR_API __declspec(dllimport)
#endif


class VECTOR_API Vector {
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