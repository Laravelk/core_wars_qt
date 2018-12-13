#include "Instruction.h"
#include "Core.h"
#include "Mars.h"
#include "Factory.h"

class Instr_NOP : public Instruction
{
public:
    Instr_NOP(const InstructionData &data) : Instruction(data){}


    void Print()const override
    {
        std::cout << "NOP";
    }

    void RunInstruction(ReadyDataForCommand &data) override
    {
        UpdateData(data);
    }

    std::string GetOperation() override
    {
        return std::string("MOD");
    }
};


namespace
{
    Instruction *create_NOP(const InstructionData &idata)
    {
        return new Instr_NOP(idata);
    }

    bool b = Factory::GetInstance()->RegisterFunction("NOP", create_NOP);
}
