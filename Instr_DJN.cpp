#include "Instruction.h"
#include "Core.h"
#include "Mars.h"
#include "Factory.h"

class Instr_DJN : public Instruction
{
public:
    Instr_DJN(const InstructionData &idata) : Instruction(idata){}

    void Print()const override
    {
        std::cout << "DJN";
    }

    void RunInstruction(ReadyDataForCommand &data) override
    {
        UpdateData(data);

        SetAddressB(GetAddressB() - 1);
        if (GetAddressB() != 0){
          data.JumpToTask(GetAddressA());
        }
    }


    std::string GetOperation() override
    {
        return std::string("DJN");
    };
};

namespace
{
    Instruction *create_DJN(const InstructionData &idata)
    {
        return new Instr_DJN(idata);
    }


    bool b = Factory::GetInstance()->RegisterFunction("DJN", create_DJN);
}
