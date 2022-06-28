#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>
template<typename T, int N>
class Vector_G{
private:
    T coordinates[N]{};
    size_t capacity = N;
public:
    Vector_G<T,N>& operator+(Vector_G<T,N> const &v2){
        Vector_G<T,N> new_v;
        for(unsigned i=0; i<N;i++){
            new_v.coordinates = coordinates[i]+v2.coordinates[i];
        }
        return new_v;
    }
    Vector_G<T,N>& operator-(Vector_G<T,N> const &v2){
        Vector_G<T,N> new_v;
        for(unsigned i=0; i<N;i++){
            new_v.coordinates = coordinates[i]-v2.coordinates[i];
        }
        return new_v;
    }

    Vector_G<T,N>& operator*(T num){
        for(auto& item:coordinates){
            item*=num;
        }
        return *this;
    }
    bool operator<(Vector_G<T,N> const &v2){
        long answ=0;
        for(unsigned i=0;i<N;i++){
            answ+=coordinates[i]*coordinates[i]-v2.coordinates[i]*v2.coordinates[i];
        }
        if(answ<=0){
            return false;
        }
        else{
            return true;
        }
    }
    bool operator>(Vector_G<T,N> const &v2){
        return !*this<v2;
    }
    Vector_G<T,N>& operator= (const Vector_G<T,N> &v2){
        memcpy(coordinates, v2.coordinates);
        return *this;
    }

};
template<typename T>
class Vector_G<T, -1>{
private:
    T* coordinates;
    size_t capacity = 0;
public:
    explicit Vector_G(size_t N):coordinates(new T[N]), capacity(N){};
    Vector_G& operator+(Vector_G const &v2){
        assert(v2.capacity==capacity);
        Vector_G<T,-1> new_v(v2.capacity);
        for(unsigned i=0; i<v2.capacity;i++){
            new_v.coordinates[i] = coordinates[i]+v2.coordinates[i];
        }
        return new_v;
    }
    Vector_G& operator-(Vector_G const &v2){
        assert(v2.capacity==capacity);
        Vector_G<T,-1> new_v(v2.capacity);
        for(unsigned i=0; i<v2.capacity;i++){
            new_v.coordinates[i] = coordinates[i]-v2.coordinates[i];
        }
        return new_v;
    }

    Vector_G& operator*(T num){
        for(auto& item:coordinates){
            item*=num;
        }
        return *this;
    }
    bool operator<(Vector_G const &v2){
        assert(capacity==v2.capacity);
        long answ=0;
        for(unsigned i=0;i<v2.capacity;i++){
            answ+=coordinates[i]*coordinates[i]-v2.coordinates[i]*v2.coordinates[i];
        }
        if(answ<=0){
            return false;
        }
        else{
            return true;
        }
    }
    bool operator>(Vector_G const &v2){
        return !*this<v2;
    }
    Vector_G& operator= (const Vector_G &v2){
        delete[] coordinates;
        T* new_coord = new T[v2.capacity];
        memcpy(new_coord, v2.coordinates, v2.capacity);
        coordinates = new_coord;
        return *this;
    }


    void resize(size_t size){
        T* new_coord = new T[size]{};
        memcpy(coordinates, new_coord, size);
        delete[] coordinates;
        coordinates = new_coord;
    }
    ~Vector_G(){
        delete[] coordinates;
    }
};
int main() {
    Vector_G<int, 5>a{};

    return 0;
}
