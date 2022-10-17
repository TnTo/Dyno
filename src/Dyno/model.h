#pragma once

#include <vector>

#include "utils.h"

namespace Dyno {

class Agent;

class Model
{
public:
    Model();
    ~Model();

    template <isAgent T>
    T* add_agent();

    template <isAgent T>
    void add_agents(int n);

    template <isAgent T=Agent>
    int get_n_of_agents();

protected:
    std::vector<Agent> agents_list;

private:
    int N;
    int get_next_id();
};

}