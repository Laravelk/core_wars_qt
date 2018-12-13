#include "Instruction.h"
#include "Core.h"
#include "Mars.h"
#include "Factory.h"

class Instr_JMP : public Instruction
{
public:
    Instr_JMP(const InstructionData &idata): Instruction(idata){}

    void Print()const override
    {
        std::cout << "JMP";
    }

    void RunInstruction(ReadyDataForCommand &data)
    {
        UpdateData(data);
        data.JumpToTask((data.currentlyCommandAddress + GetAddressA()) % data.GetCoreSize());
        return;
    }

    std::string GetOperation() override
    {
        return std::string("JMP");
    };
};

namespace
{
    Instruction *create_JMP(const InstructionData &idata)
    {
        return new Instr_JMP(idata);
    }

    bool b = Factory::GetInstance()->RegisterFunction("JMP", create_JMP);
}
