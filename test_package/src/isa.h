#include <catch2/catch_all.hpp>

#include <memory>

#include "Dyno.h"

class A {
public:
    virtual ~A() = default;
};
class B : public A {};

TEST_CASE( "IsA", "[base]" ) {
    std::shared_ptr<A> a = std::shared_ptr<A>(new A());
    std::shared_ptr<B> b = std::shared_ptr<B>(new B());
    std::shared_ptr<A> ab = std::shared_ptr<A>(new B());

    REQUIRE(Dyno::isA<A>(a));
    REQUIRE(Dyno::isA<A>(b));
    REQUIRE(Dyno::isA<A>(ab));
    REQUIRE_FALSE(Dyno::isA<B>(a));
    REQUIRE(Dyno::isA<B>(b));
    REQUIRE(Dyno::isA<B>(ab));
}
