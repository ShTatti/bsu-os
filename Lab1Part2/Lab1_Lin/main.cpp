#include <iostream>

#include "../num/library.h"
#include "../vec/vec.h"

int main() {
    Number num1(12.1);
    Number num2(2);
    std::cout << (num1 * num2).getNumber() << '\n';
    Vector v = VECTOR_ONE;
    std::cout << v.calculatePolarRadius().getNumber() << '\n';
    std::cout << v.calculatePolarAngle().getNumber() << '\n';
    std::cout << (v + v).calculatePolarRadius().getNumber();
}
