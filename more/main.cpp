//
// Created by aleksandr on 02.07.22.
//
#include <cassert>
#include <array>
#include <vector>
#include <initializer_list>
#include <iostream>
#include <utility>
#include <algorithm>


template <typename Type>
concept Vector_type = requires(Type P) {{P}->std::convertible_to<int>;};
template<typename T>
concept IsContainer = requires(T &&container){ (std::begin(container)); };
template<typename T>
concept TypeForUs = Vector_type<T>|| IsContainer<T>;

template <TypeForUs Type, int N>
class Vector {
    static_assert(N >= 0);
    std::array<Type, N> data_;

public:
    constexpr Vector()= default;
    constexpr Vector(const Vector<Type, N>& other):data_(other.data_){
    }
    constexpr Vector(std::initializer_list<Type>&& other){
        std::copy(other.data_,other.data_+N, data_);
    }
    constexpr Vector(const Vector<Type, N>&& other):data_(std::move(other.data_)){
    }
    const Type& operator[](unsigned int i) const{
        return data_[i];
    }
    Type& operator[](unsigned int i){
        return data_[i];
    }
    Type norm() const{
        Type sum=0;
        for(auto& i:data_){
            sum+=i*i;
        }
        return sum;
    }
    Vector<Type, N> operator*=(Type num){
        for(auto& i:data_){
            i*=i;
        }
        return *this;
    }
    Vector<Type, N> operator/=(Type num){
        for(auto& i:data_){
            i/=i;
        }
        return *this;

    }
    Vector<Type, N> operator+=(Vector<Type, N>&& other){
        for(unsigned i=0; i<N;++i){
            data_[i]+=other.data_[i];
        }
        return std::forward<Type>(*this);
    }
    Vector<Type, N> operator-=(const Vector<Type, N>& other){
        for(unsigned i=0; i<N;++i){
            data_[i]-=other.data_[i];
        }
        return std::forward<Type>(*this);
    }

    Vector<Type, N> operator*(Type num) const{
        Vector<Type, N>new_v = *this;
        new_v*=num;
        return std::forward<Type>(new_v);
    }
    Vector<Type, N> operator/(Type num) const{
        Vector<Type, N>new_v = *this;
        new_v/=num;
        return std::forward<Type>(new_v);
    }
    Vector<Type, N> operator+(const Vector<Type, N>&& other) const{
        Vector<Type, N>new_v = *this;
        new_v+=other;
        return std::forward<Type>(new_v);
    }
    Vector<Type, N> operator-(const Vector<Type, N>& other) const{
        Vector<Type, N>new_v = *this;
        new_v+=other;
        return std::forward<Type>(new_v);
    }

    friend Vector<Type, N> operator*(Type num, const Vector<Type, N>&& vec);
    friend std::ostream operator<<(std::ostream& out,  const Vector<Type, N>&& vec);
};
template<TypeForUs Type, int N>
std::ostream operator<<(std::ostream& out,  const Vector<Type, N>&& vec){
    for(auto& i: vec.data_){
        out<<i<<" ";
    }
}
template<TypeForUs Type, int N>
Vector<Type, N> operator*(Type num, const Vector<Type, N>&& vec){
    Vector<Type,N>new_v = vec;
    new_v*=num;
    return std::forward<Type, N>(new_v);
}

constexpr int Dynamic = -1;

template <TypeForUs Type>
class Vector<Type, Dynamic> {
    std::vector<Type> data_;
    int size_;

public:
    constexpr Vector();
    constexpr Vector(const Vector<Type, Dynamic>& other):data_(other.data_), size_(other.size_){
    }
    constexpr Vector(const Vector<Type, Dynamic>&& other):
    data_(std::move(other.data_)), size_(std::exchange(other.size_,0)){

    }
    constexpr Vector(std::initializer_list<Type>&& other){
        data_ = other.data_;
        size_ = other.data_.size();
    }

    const Type& operator[](unsigned int i) const{
        return data_[i];
    }
    Type& operator[](unsigned int i){
        return data_[i];
    }
    Type norm() const{
        Type sum=0;
        for(auto& i:data_){
            sum+=i*i;
        }
        return std::forward<Type>(sum);
    }

    Vector<Type, Dynamic> operator*=(Type num){
        for(auto& i:data_)
            i*=num;
        return *this;
    }
    Vector<Type, Dynamic> operator/=(Type num){
        for(auto& i:data_)
            i*=num;
        return *this;
    }
    Vector<Type, Dynamic> operator+=(const Vector<Type, Dynamic>& other){
        assert(other.size_==size_);
        for(unsigned i=0; i<size_;++i){
            data_[i]+=other.data_[i];
        }
        return std::forward<Type>(*this);
    }
    Vector<Type, Dynamic> operator-=(const Vector<Type, Dynamic>& other){
        assert(other.size_==size_);
        for(unsigned i=0; i<size_;++i){
            data_[i]-=other.data_[i];
        }
        return std::forward<Type>(*this);
    }

    Vector<Type, Dynamic> operator*(Type num) const{

        Vector<Type,Dynamic>new_v = *this;
        new_v*=num;
        return std::forward<Type, Dynamic>(num);
    }
    Vector<Type, Dynamic> operator/(Type num) const{
        Vector<Type,Dynamic>new_v = *this;
        new_v/=num;
        return std::forward<Type, Dynamic>(num);
    }
    Vector<Type, Dynamic> operator+(const Vector<Type, Dynamic>& other) const{
        assert(other.size_==size_);
        Vector<Type,Dynamic>new_v = *this;
        for(unsigned i=0; i<size_;i++)
            new_v[i]+=other.data_[i];
        return std::forward<Type, Dynamic>(new_v);
    }
    Vector<Type, Dynamic> operator-(const Vector<Type, Dynamic>& other) const{
        assert(other.size_==size_);
        Vector<Type,Dynamic>new_v = *this;
        for(unsigned i=0; i<size_;i++)
            new_v[i]+=other.data_[i];
        return std::forward<Type, Dynamic>(new_v);
    }

    friend Vector<Type, Dynamic> operator*(Type num, const Vector<Type, Dynamic>&& vec);
    friend std::ostream operator<<(std::ostream& out,  const Vector<Type, Dynamic>&& vec);
};
template<TypeForUs Type>
std::ostream operator<<(std::ostream& out,  const Vector<Type, Dynamic>&& vec){
    for(auto& i: vec.data_){
        out<<i<<" ";
    }
}
template<TypeForUs Type>
Vector<Type, Dynamic> operator*(Type num, const Vector<Type, Dynamic>&& vec){
    Vector<Type,Dynamic>new_v = vec;
    new_v*=num;
    return std::forward<Type, Dynamic>(new_v);
}
