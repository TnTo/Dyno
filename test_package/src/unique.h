#include <catch2/catch_all.hpp>

#include "Dyno.h"

class Base : public Dyno::Unique<Base> {};

TEST_CASE( "Unique Agent", "[base]" ) {
    {
        Base b = Base();
        REQUIRE_THROWS_AS(Base(), Dyno::UniqueException);
    }
    REQUIRE_NOTHROW(Base());

}
