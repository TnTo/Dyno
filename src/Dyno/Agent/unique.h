#pragma once

#include <exception>

namespace Dyno {

class UniqueException: public std::exception
{
    const char* what() const throw()
    {
        return "Instancing a second unique agent";
    }
};

template <class T>
class Unique
{
    static bool instanced;

public:
    Unique() {
        if (instanced) {
            throw UniqueException();
        };
        instanced = true;
    };

    ~Unique() {
        instanced = false;
    };

};

template<class T>
bool Unique<T>::instanced = false;

}