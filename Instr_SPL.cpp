#include "Instruction.h"
#include "Core.h"
#include "Mars.h"
#include "Factory.h"

class Instr_SPL : public Instruction
{
public:
    Instr_SPL(const InstructionData &data) : Instruction(data){}


    void Print()const override
    {
        std::cout << "SPL";
    }

    void RunInstruction(ReadyDataForCommand &data) override
    {
        UpdateData(data);
        data.AddWarriorInGame((data.NRPA + data.currentlyCommandAddress) % data.GetCoreSize());
    }

    std::string GetOperation() override
    {
        return std::string("SPL");
    };
};


namespace
{
    Instruction *create_SPL(const InstructionData &idata)
    {
        return new Instr_SPL(idata);
    }

    bool b = Factory::GetInstance()->RegisterFunction("SPL", create_SPL);
}

