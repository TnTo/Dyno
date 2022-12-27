#pragma once

#include <concepts>
#include <memory>

namespace Dyno {

class Agent;

template<class T>
concept isAgent = std::derived_from<Agent, T>;

template<class T>
bool isA(auto x) {
    return (std::dynamic_pointer_cast<T>(x) != NULL);
}


}