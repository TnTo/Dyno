#pragma once

#include <algorithm>
#include <memory>
#include <ranges>
#include <vector>

#include "utils.h"

namespace Dyno {

class Agent;

class Model
{
public:

    Model() {};
    ~Model() {};

    template <isAgent T>
    std::weak_ptr<T> add_agent() {
        agents_list.emplace_back(std::shared_ptr<T>(new T(this, get_next_id())));
        return agents_list.back();
    };

    template <isAgent T>
    void add_agents(int n) {
        for (int i = 0; i < n; i++) {
            add_agent<T>();
        }
    };

    template <isAgent T=Agent>
    int get_n_of_agents() {
        return std::count_if(agents_list.begin(), agents_list.end(), ([](auto x) {
            return isA<T>(x);
        }));
    };

protected:
    std::vector<std::shared_ptr<Agent>> agents_list = std::vector<std::shared_ptr<Agent>> { };

private:
    int N = 0 ;
    int get_next_id() {
        return ++N;
    };
};

}