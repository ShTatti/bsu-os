#ifndef NUM_LIBRARY_H
#define NUM_LIBRARY_H

class Number {
private:
    double number;

public:
    Number();
    Number(double number);

    double getNumber();
    void setNumber(double number);

    Number operator+(const Number& number);
    Number operator-(const Number& number);
    Number operator*(const Number& number);
    Number operator/(const Number& number);
};

const Number NUMBER_ZERO = Number(0.0);
const Number NUMBER_ONE = Number(1.0);

Number createNumber(double number);

#endif //NUM_LIBRARY_H
