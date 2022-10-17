#include <ranges>

#include "model.h"
#include "agent.h"

using namespace Dyno;

Model::Model()
{
    N = 0;
    agents_list = std::vector<Agent> { };
}

int Model::get_next_id() {
    return ++N;
}

template <isAgent T>
T* Model::add_agent() {
    agents_list.emplace_back(this, get_next_id());
    return agents_list.back();
}

template <isAgent T>
void Model::add_agents(int n) {
    for (int i = 0; i < n; i++) {
        add_agent<T>();
    }
}

template <isAgent T>
int Model::get_n_of_agents() {
    return (agents_list | std::ranges::views::filter(isA<T>) | std::ranges::size);
}