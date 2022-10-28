#pragma once

namespace Dyno {

class Model;

class Agent
{
public:
    Agent(const Model* m, int id): m(m), id(id) { };
    ~Agent() {};

    int get_id() {
        return id;
    };

protected:
    const Model* m;
    const int id;

};

}

//  MyArray(const MyArray& a) = delete;
//  MyArray& operator=(const MyArray& a) = delete;