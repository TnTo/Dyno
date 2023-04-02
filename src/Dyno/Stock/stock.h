#pragma once

#include "../config.h"

namespace Dyno {

class Stock
{
    virtual dynoType get_price() = 0;
    virtual dynoType get_quantity() = 0;

    virtual dynoType get_value() {
        return get_price() * get_quantity();
    };
};

}