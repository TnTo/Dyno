#include <catch2/catch_all.hpp>

#include <iostream>

#include "Dyno.h"

TEST_CASE( "Base Model", "[base]" ) {
    Dyno::Model m = Dyno::Model{ };
    Dyno::Agent* a = m.add_agent<Dyno::Agent>();

    std::cout << a -> get_id() << std::endl;
    std::cout << m.get_n_of_agents() << std::endl;

}
