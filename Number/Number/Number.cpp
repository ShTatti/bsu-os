#include "Number.h"

Number::Number() {
	number = 0;
}

Number::Number(double number) {
	this->number = number;
}

double Number::getNumber() {
	return number;
}

void Number::setNumber(double number) {
	this->number = number;
}

Number Number::operator+(const Number& number) {
	return Number(this->number + number.number);
}

Number Number::operator-(const Number& number) {
	return Number(this->number - number.number);
}

Number Number::operator*(const Number& number) {
	return Number(this->number * number.number);
}

Number Number::operator/(const Number& number) {
	if (number.number == 0) {
		throw "eror.division by zero";
	}
	return Number(this->number / number.number);
}

Number createNumber(double number) {
	return Number(number);
}