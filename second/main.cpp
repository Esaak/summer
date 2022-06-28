#include <iostream>
#include <chrono>
/*template<unsigned N>
constexpr unsigned factorial(){
    if constexpr(N==1 || N==0){
        return 1;
    }
    else{
        return factorial<N-1>()*N;
    }

}*/

template<unsigned N>
constexpr unsigned factorial(){
    if constexpr(N==1 || N==0){
        return 1;
    }
    else{
        unsigned answ =1;
        for(unsigned i=2;i<=N;i++){
            answ*=i;
        }
        return answ;
    }

}
int main() {
    auto start = std::chrono::steady_clock::now();
    std::cout<<factorial<10>();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << elapsed_seconds.count() << "s\n";
    return 0;
}
