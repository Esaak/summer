//
// Created by ilya on 02.07.22.
//
#pragma once
#include <string>
#include <memory>
#include <utility>
/*
template <typename Object, typename = decltype(std::declval<Object>().to_string())>
std::string makeString(const Object& object){
    return object.to_string();
}

namespace Impl {bool acceptNumber(int);}

template<typename Numeric>
std::string makeString(Numeric value, decltype(Impl::acceptNumber(value))* = nullptr){
    return std::to_string(value);
}
*/
namespace Impl{
    template<typename MaybeString>
    inline constexpr bool isString = std::is_convertible_v<MaybeString, std::string>;
    template<> inline constexpr bool isString<std::string_view> = true;
}
template <typename Object>
auto makeString(const Object &object)-> decltype(object.to_string()){
    return object.to_string();
}

template<typename Numeric>
auto makeString(Numeric value)->decltype(std::to_string(value)){
    return std::to_string(value);
}
template<typename Iterable>
auto makeString(const Iterable& iterable)->std::enable_if_t<!Impl::isString<Iterable>,
decltype(makeString(*std::begin(iterable)))>{
    std::string result;
    for(const auto& i : iterable){
        if(!result.empty())
            result+=';';
        result+= makeString(i);
    }

    return result;
}
template<typename String>
auto makeString(String&& s)->std::enable_if_t<Impl::isString<String>, std::string>{
    return std::string(std::forward<String>(s));
}
/*
template<typename First, typename Second, typename... Rest>
auto makeString(First&& first, Second&& second, Rest&& ...rest)->std::string {
    return makeString(std::forward<First>(first)) + makeString(std::forward<Second>(second),std::forward<Rest>(rest)...);
}
*/
template<typename ...Pack>
auto makeString(Pack&& ...pack)-> std::enable_if_t<(sizeof...(Pack)>1), std::string >{
    return (...+=makeString(std::forward<Pack>(pack)));
}


//////////////////////////////////////////////////////////////////////
namespace Impl_e {


    template<typename T>
    concept HasStdConversion = requires(T number){ std::to_string(number); };
    template<typename T>
    concept HasToString = requires(T &&object){
        { object.to_string() } ->std::convertible_to<std::string>;
    };

    template<HasToString Object>
    std::string makeString(Object &&object) {
        return object.to_string();
    }

    template<typename T>
    concept IsContainer = !Impl_e::HasToString<T> && requires(T &&container){ (std::begin(container)); };


    template<typename T>
    concept IsString = IsContainer<T> && std::constructible_from<std::string, T>;


}
//template<typename T>
//concept IsString = std::is_convertible_v<T, std::string>|| std::is_same_v<T, std::string_view>;
template<Impl_e::HasToString Object>
std::string makeString(Object&& object){
    return object.to_string();
}

template <Impl_e::HasStdConversion Numeric>
std::string makeString(Numeric&& value)
{
    return std::to_string(std::forward<Numeric>(value));
}

template <Impl_e::IsString String>
std::string makeString(String&& s)
{
    return std::string(std::forward<String>(s));
}

template <Impl_e::IsContainer Container>
std::string makeString(Container&& iterable)
{
    std::string result;
    for (auto&& i: std::forward<Container>(iterable))
    {
        if (!result.empty())
            result += ';';
        result += makeString(std::forward<decltype(i)>(i));
    }

    return result;
}

template <typename... Pack>
requires(sizeof...(Pack) > 1)
std::string makeString(Pack&&... pack)
{
    return (... += makeString(std::forward<Pack>(pack)));
}
