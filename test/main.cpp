#include <iostream>
#include <algorithm>
#include <array>
#include <string>
#include <numeric>
#include <vector>
#include <type_traits>
template<typename T>
concept UnsignedWith = requires(T&&x) {{x+1}->std::same_as<unsigned >;};
template<UnsignedWith P>
struct A{
    void foo(){
        P a=6;
        std::cout<<a;
    }
};
/*
template <typename Type>
concept Vector_type = requires(Type P) {{P}->std::convertible_to<int>;};
template<Vector_type T>
struct A{
    void foo(){
        std::cout<<1;
    }
};*/
int main() {

    //std::string a = "ass";
    //static_cast<int>(a);
    //A<std::string> b;
    //b.foo();
    A<-5>c;
    c.foo();
    return 0;
}
