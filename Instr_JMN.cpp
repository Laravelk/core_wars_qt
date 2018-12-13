#include "Instruction.h"
#include "Core.h"
#include "Mars.h"
#include "Factory.h"

class Instr_JMN : public Instruction
{
public:
    Instr_JMN(const InstructionData &idata) : Instruction(idata){}

    void Print()const override
    {
        std::cout << "JMN";
    }

    void RunInstruction(ReadyDataForCommand &data) override
    {
        UpdateData(data);
        if (GetAddressB() == 0)
        {
          data.JumpToTask(GetAddressA());
        }
    }


    std::string GetOperation() override
    {
        return std::string("JMN");
    };
};

namespace
{
    Instruction *create_JMN(const InstructionData &idata)
    {
        return new Instr_JMN(idata);
    }


    bool b = Factory::GetInstance()->RegisterFunction("JMN", create_JMN);
}

