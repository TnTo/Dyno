#pragma once

#include <concepts>
#include <memory>

namespace Dyno {

template<typename T>
using ptr = std::weak_ptr<T>;

template<class T>
bool isA(auto x) {
    return (std::dynamic_pointer_cast<T>(x) != NULL);
}

template<class Base, class T>
concept is = std::derived_from<Base, T>;

}