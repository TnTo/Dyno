#pragma once

namespace Dyno {

template <class T>
class Stock
{
    virtual auto get_price() = 0;
    virtual auto get_quantity() = 0;

    virtual auto get_value() {
        return get_price() * get_quantity();
    };
};

}