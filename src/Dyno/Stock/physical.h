#pragma once

#include "stock.h"

namespace Dyno {

template <class T>
class AgentWithPhysicalStock;

template <class T>
class PhysicalStock : public Stock
{
    virtual AgentWithPhysicalStock<T> get_owner() = 0;
};

}