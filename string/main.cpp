#include <iostream>
#include <vector>
#include <set>
#include "makeString.h"

struct A{
    std::string to_string() const {return "A"; }
};
struct B{
    int m_i = 0;
    std::string to_string() const {return "B{"+ std::to_string(m_i) + "}";}
};
int main() {

    A a;
    B b = {1};
    const std::vector<int> xs = {1,2,3};
    std::set<float> ys;
    ys.insert(4);
    ys.insert(5);
    ys.insert(6);
    const double zs[] = {7,8,9};
    std::cout << "a: " << makeString(a) <<"b: "<<makeString(b)<<"pi: "<<makeString(3.14)<<"\n"
    << makeString(xs)<<"\n"<<makeString(ys)<<"\n"<<makeString(zs)<<"\n";
    std::cout << makeString("Hello, ")
              << makeString(std::string_view("world"))
              << makeString(std::string("!!1"))
              << std::endl;
    std::cout << makeString("xs: ", xs, "; and float is: ", 3.14f)
              << std::endl;
    return 0;
}
