#pragma once

#include <concepts>
#include <cstddef>

namespace Dyno {

class Agent;

template<class T>
concept isAgent = std::derived_from<Agent, T>;

template<class T>
bool isA(const auto* x) {
    return (dynamic_cast<const T*>(x) != NULL);
}

}