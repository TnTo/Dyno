#include <catch2/catch.hpp>

#include "dyno.hpp"

TEST_CASE("Model creation") {
    dyno::Model m {"model"};
    REQUIRE(m.name == "model");
}