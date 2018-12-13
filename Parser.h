#pragma once

#include <fstream>
#include "Mars.h"

class Parser{
public:
    static Parser* GetInstance() {
        static Parser f;
        return &f;
    }

    WarData ParserWarData(std::ifstream &inputFile);
    ReadyInstruction ParserInstruction(const std::string line)const;
private:
    Mode StrToMode(const std::string mode)const;
    Modifier StrToModifier(const std::string modefier)const;
    //Parser() = default;
};
