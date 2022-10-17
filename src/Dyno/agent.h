#pragma once

namespace Dyno {

class Model;

class Agent
{
public:
    Agent(const Model* m, int id);
    ~Agent();

    int get_id();

protected:
    const Model* m;
    const int id;

};

}