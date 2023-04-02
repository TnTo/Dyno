# pragma once

#include "../utils.h"

namespace Dyno {

class Stock;

template<class T>
concept isStock = is<Stock, T>;

}