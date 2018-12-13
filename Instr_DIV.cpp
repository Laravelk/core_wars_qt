#include "Instruction.h"
#include "Core.h"
#include "Mars.h"
#include "Factory.h"
class Instr_DIV : public Instruction
{
public:
    Instr_DIV(const InstructionData &idata) : Instruction(idata) {}

    void Print()const override
    {
        std::cout << "DIV";
    }

    void RunInstruction(ReadyDataForCommand &data) override
    {
        UpdateData(data);
        bool deleteWarrior = false;

        switch(GetModifier()){

            case A:
            {
                if (data.GetAPtrForRead()->GetAddressA() != 0)
                {
                    data.GetBPtrForWrite()->SetAddressA((data.GetBPtrForWrite()
                        ->GetAddressA()/ data.GetAPtrForRead()->GetAddressA()) % data.GetCoreSize());
                }
                else
                {
                    deleteWarrior = true;
                }
                break;
            }

            case B:
            {
                if (data.GetAPtrForRead()->GetAddressB() != 0)
                {
                    data.GetBPtrForWrite()->SetAddressB((data.GetBPtrForRead()
                        ->GetAddressB() / data.GetAPtrForRead()->GetAddressB()) % data.GetCoreSize());
                }
                else
                {
                    deleteWarrior = true;
                }
                break;
            }

            case AB:
            {
                if (data.GetAPtrForRead()->GetAddressA() != 0)
                {
                    data.GetBPtrForWrite()->SetAddressB((data.GetBPtrForRead()
                        ->GetAddressB() / data.GetAPtrForRead()->GetAddressA()) % data.GetCoreSize());
                }
                else
                {
                    deleteWarrior = true;
                }
                break;
            }

            case BA:
            {
                if (data.GetAPtrForRead()->GetAddressB() != 0)
                {
                    data.GetAPtrForWrite()->SetAddressA((data.GetAPtrForRead()
                        ->GetAddressA()/ data.GetAPtrForRead()->GetAddressB()) % data.GetCoreSize());
                }
                else
                {
                    deleteWarrior = true;
                }
                break;
            }

            case F:

            case I:
            {
                if ((data.GetAPtrForRead()->GetAddressB() != 0) && (data.GetAPtrForRead()->GetAddressA() != 0))
                {
                    data.GetBPtrForWrite()->SetAddressA((data.GetBPtrForRead()
                        ->GetAddressA()/ data.GetAPtrForRead()->GetAddressA()) % data.GetCoreSize());

                    data.GetAPtrForWrite()->SetAddressB((data.GetAPtrForRead()
                        ->GetAddressB() / data.GetAPtrForRead()->GetAddressB()));
                }
                else
                {
                    deleteWarrior = true;
                }
                break;
            }

            case X:
            {
                if ((data.GetAPtrForRead()->GetAddressB() != 0) && (data.GetAPtrForRead()->GetAddressA() != 0))
                {
                    data.GetBPtrForWrite()->SetAddressA((data.GetBPtrForRead()
                        ->GetAddressA()/ data.GetAPtrForRead()->GetAddressB()) % data.GetCoreSize());

                    data.GetBPtrForWrite()->SetAddressB((data.GetBPtrForRead()
                        ->GetAddressB() / data.GetAPtrForRead()->GetAddressA()) % data.GetCoreSize());
                }
                else
                {
                    deleteWarrior = true;
                }
                break;
            }

            default:
            {
                throw std::invalid_argument("invalid modifier");
            }
        }

        if (deleteWarrior)
        {
            data.DeleteWarriorFromGame();
        }

    }

    std::string GetOperation() override
    {
        return std::string("DIV");
    };
};

namespace
{
    Instruction *create_DIV(const InstructionData &idata)
    {
        return new Instr_DIV(idata);
    }


    bool b = Factory::GetInstance()->RegisterFunction("DIV", create_DIV);
}

