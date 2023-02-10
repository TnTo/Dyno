# pragma once

# include "../utils.h"

namespace Dyno {

class Agent;

template<class T>
concept isAgent = is<Agent, T>;

}