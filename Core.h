#pragma once

#include <vector>
#include <memory>

#include "Factory.h"
#include "Instruction.h"


class Core
{
public:
    Core(int core_size, const ReadyInstruction &default_instr): CORE_SIZE(core_size), defInstr(default_instr),
                                                                coreMemory_(core_size)
    {
        for (int i = 0; i < CORE_SIZE; ++i)
        {
          LoadInstruction(default_instr, i);
        }

    }

    Instruction *operator[](int index);

    void LoadInstruction(const ReadyInstruction &instr, int index);
    void Reset(int index, Instruction *instr);

    void Print()const;

    const int CORE_SIZE;

private:
    ReadyInstruction defInstr;
    std::vector <std::unique_ptr<Instruction>> coreMemory_;
};
