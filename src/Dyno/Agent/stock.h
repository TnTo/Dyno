#pragma once

#include <concepts>

#include "agent.h"
#include "../utils.h"
#include "../Stock/utils.h"

namespace Dyno {

template <class T>
class PhysicalStock;

template <class T>
class FinancialStock;

template <class T>
class AgentWithStock : public Agent
{
    virtual dynoType get_stock_value<T>() = 0;
};

template <class T>
class AgentWithPhysicalStock : public AgentWithStock<T>
{};

template <class T>
class AgentWithFinancialStock : public AgentWithStock<T>
{};

template <class T>
class Lender : public AgentWithFinancialStock<T>
{};

template <class T>
class Borrower : public AgentWithFinancialStock<T>
{};



}