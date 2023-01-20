#include <catch2/catch_all.hpp>

#include <memory>

#include "Dyno.h"

TEST_CASE( "Base Model", "[base]" ) {
    Dyno::Model m = Dyno::Model{ };
    std::weak_ptr<Dyno::Agent> a = m.add_agent<Dyno::Agent>();

    REQUIRE(a.lock() -> get_id() == 1);
    REQUIRE(m.get_n_of_agents() == 1);

}
