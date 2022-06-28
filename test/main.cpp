#include <iostream>
template<typename T, int N>
struct A{
      void foo(){
          std::cout<<1;
      }
};
template<typename T>
struct A <T, -1>{
    void foo(){
        std::cout<<2;
    }
};
template<typename T>
struct A <T, typename U>{

};
int main() {
    A<int,-1>a;
    a.foo();
    return 0;
}
