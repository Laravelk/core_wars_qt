#pragma once

#include <unordered_map>
#include <functional>

#include "Instruction.h"

class Factory {
public:
    using creatorF = std::function<Instruction*(const InstructionData&)>;

    static Factory* GetInstance() {
        static Factory f;
        return &f;
    }


    Instruction* create(const std::string& id, const InstructionData& data) {
        return creators[id](data);
    }


    bool RegisterFunction(const std::string &id, creatorF creator) {
        creators[id] = creator;
        return true;
    }


private:
    std::unordered_map<std::string, creatorF> creators;
};