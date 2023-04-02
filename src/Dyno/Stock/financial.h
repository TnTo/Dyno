#pragma once

#include "stock.h"
#include "utils.h"

namespace Dyno {

template <class T>
class Borrower;

template <class T>
class Lender;

template <class T>
class FinancialStock : public Stock
{
    virtual Borrower<T> get_borrower() = 0;
    virtual Lender<T> get_lender() = 0;
};

}