module;

import <string>;

export module dyno.model;

export namespace dyno {

    class Model {
        public:
            const std::string name;

            Model(std::string n) : name(n) {}
    };

};