#include "Instruction.h"
#include "Core.h"
#include "Mars.h"
#include "Factory.h"
class Instr_DAT : public Instruction
{
public:
    Instr_DAT(const InstructionData &idata): Instruction(idata){}

    void Print()const override
    {
        std::cout << "DAT";
    }

    void RunInstruction(ReadyDataForCommand &data) override
    {
        UpdateData(data);
        data.DeleteWarriorFromGame();
    }

    std::string GetOperation() override
    {
        return std::string("DAT");
    }
};


namespace
{
    Instruction *create_DAT(const InstructionData &idata)
    {
        return new Instr_DAT(idata);
    }


    bool b = Factory::GetInstance()->RegisterFunction("DAT", create_DAT);
}
