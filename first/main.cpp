#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <chrono>
//const double pi = std::acos(-1);
struct Point{
    double x;
    double y;
};
//std:: ostream& operator<< (std::ostream& os ,const matrix &matrix2) {}

std::vector<Point>terribleTrigonometry(unsigned n){
    if(n==0){
        return {};
    }
    std::vector<Point>answ;
    answ.reserve(n);
    for(unsigned i=0;i<n; i++){
        answ.push_back({cos(2*M_PI/n*i),sin(2*M_PI/n*i)});
    }
    return answ;
}

std::vector<Point>terribleTrigonometry_2(unsigned n){
    if(n==0){
        return {};
    }
    std::vector<Point>answ;
    answ.resize(n);
    answ[0] = {1,0};
    answ[1] = {cos(2*M_PI/n),sin(2*M_PI/n)};
    for(unsigned i=2; i<n; i++){
        answ[i] = {answ[i-1].x*answ[1].x-answ[i-1].y*answ[1].y, answ[i-1].y*answ[1].x + answ[i-1].x*answ[1].y};
    }
    return answ;
}

int main() {
    auto start = std::chrono::steady_clock::now();
    std::vector<Point>a = terribleTrigonometry(5);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << elapsed_seconds.count() << "s\n";
    auto start1 = std::chrono::steady_clock::now();
    std::vector<Point>b = terribleTrigonometry_2(5);
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = end1-start1;
    std::cout << elapsed_seconds1.count() << "s\n";
    std::cout<<std::fixed;
    std::cout<<std::setprecision(5);
    /*for(int i=0; i<b.size();i++ ){
        std::cout<<a[i].x<<" "<<a[i].y<<'\t'<<b[i].x<<" "<<b[i].y<<"\n";
    }*/
    return 0;
}
