#include "Instruction.h"
#include "Core.h"
#include "Mars.h"
#include "Factory.h"

class Instr_JMZ : public Instruction
{
public:
    Instr_JMZ(const InstructionData &idata) : Instruction(idata){}

    void Print()const override
    {
        std::cout << "JMN";
    }

    void RunInstruction(ReadyDataForCommand &data) override
    {
        UpdateData(data);
        if (GetAddressB() != 0)
        {
            data.JumpToTask(GetAddressA());
        }
    }

    std::string GetOperation() override
    {
        return std::string("JMZ");
    };
};

namespace
{
    Instruction *create_JMZ(const InstructionData &idata)
    {
        return new Instr_JMZ(idata);
    }


    bool b = Factory::GetInstance()->RegisterFunction("JMZ", create_JMZ);
}


