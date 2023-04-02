#pragma once

#include "stock.h"

namespace Dyno {

class HomogeneusStock : public Stock
{  
    protected:
    dynoType quantity;
    dynoType price;

    public:
    HomogeneusStock(dynoType quantity, dynoType price): quantity(quantity), price(price) { };

    dynoType get_price() {
        return price
    };

    dynoType get_quantity() {
        return quantity
    };

};



}