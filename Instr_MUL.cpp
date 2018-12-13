#include "Instruction.h"
#include "Core.h"
#include "Mars.h"
#include "Factory.h"

class Instr_MUL : public Instruction
{
public:
    Instr_MUL(const InstructionData &idata) : Instruction(idata){}

    void Print()const override
    {
        std::cout << "MUL";
    }

    void RunInstruction(ReadyDataForCommand &data) override
    {
        UpdateData(data);

        switch(GetModifier()){

            case A:
            {
                data.GetBPtrForWrite()->SetAddressA((data.GetBPtrForWrite()
                    ->GetAddressA() * data.GetAPtrForRead()->GetAddressA()) % data.GetCoreSize());
                break;
            }

            case B:
            {
                data.GetBPtrForWrite()->SetAddressB((data.GetBPtrForRead()
                    ->GetAddressB() * data.GetAPtrForRead()->GetAddressB()) % data.GetCoreSize());
            }

            case AB:
            {
                data.GetBPtrForWrite()->SetAddressB((data.GetBPtrForRead()
                    ->GetAddressB() * data.GetAPtrForRead()->GetAddressA()) % data.GetCoreSize());
                break;
            }

            case BA:
            {
                data.GetAPtrForWrite()->SetAddressA((data.GetAPtrForRead()
                    ->GetAddressA() * data.GetAPtrForRead()->GetAddressB()) % data.GetCoreSize());
                break;
            }

            case F:

            case I:
            {
                data.GetBPtrForWrite()->SetAddressA((data.GetBPtrForRead()
                    ->GetAddressA() * data.GetAPtrForRead()->GetAddressA()) % data.GetCoreSize());
                data.GetAPtrForWrite()->SetAddressB((data.GetAPtrForRead()
                    ->GetAddressB() * data.GetAPtrForRead()->GetAddressB()));
                break;
            }

            case X:
            {
                data.GetBPtrForWrite()->SetAddressA((data.GetBPtrForRead()
                    ->GetAddressA() * data.GetAPtrForRead()->GetAddressB()) % data.GetCoreSize());
                data.GetBPtrForWrite()->SetAddressB((data.GetBPtrForRead()
                    ->GetAddressB() * data.GetAPtrForRead()->GetAddressA()) % data.GetCoreSize());
                break;
            }

            default:
            {
                throw std::invalid_argument("invalid modifier");
            }
        }
    }

    std::string GetOperation() override
    {
        return std::string("MUL");
    };
};

namespace
{
    Instruction *create_MUL(const InstructionData &idata)
    {
        return new Instr_MUL(idata);
    }


    bool b = Factory::GetInstance()->RegisterFunction("MUL", create_MUL);
}




