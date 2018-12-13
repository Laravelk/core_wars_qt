#include "Instruction.h"
#include "Core.h"
#include "Mars.h"
#include "Factory.h"

class Instr_SNE : public Instruction
{
public:
  Instr_SNE(const InstructionData &data) : Instruction(data){}

    void Print()const override
    {
        std::cout << "SNE";
    }

    void RunInstruction(ReadyDataForCommand &data) override
    {
        UpdateData(data);

        switch(GetModifier())
        {
            case A:
            {
                if (data.GetAPtrForRead()->GetAddressA() != data.GetBPtrForRead()->GetAddressA())
                {
                    data.JumpToTask((data.currentlyCommandAddress + 1) % data.GetCoreSize());                }
                break;
            }

            case B:
            {
                if (data.GetAPtrForRead()->GetAddressA() != data.GetBPtrForRead()->GetAddressA())
                {
                    data.JumpToTask(data.currentlyCommandAddress + 1);
                }
                break;
            }

            case AB:
            {
                if (data.GetAPtrForRead()->GetAddressA() != data.GetBPtrForRead()->GetAddressB())
                {
                    data.JumpToTask((data.currentlyCommandAddress + 1) % data.GetCoreSize());                }
                break;
            }

            case BA:
            {
                if (data.GetAPtrForRead()->GetAddressB() != data.GetBPtrForRead()->GetAddressA())
                {
                    data.JumpToTask((data.currentlyCommandAddress + 1) % data.GetCoreSize());                }
                break;
            }

            case F:
            {
                if ((data.GetAPtrForRead()->GetAddressA() != data.GetBPtrForRead()->GetAddressA()) &&
                    (data.GetAPtrForRead()->GetAddressB() != data.GetBPtrForRead()->GetAddressB()))
                {
                    data.JumpToTask((data.currentlyCommandAddress + 1) % data.GetCoreSize());
                    break;
                }
            }

            case X:
            {
                if ((data.GetAPtrForRead()->GetAddressA() != data.GetBPtrForRead()->GetAddressB()) &&
                    (data.GetAPtrForRead()->GetAddressB() != data.GetBPtrForRead()->GetAddressA()))
                {
                    data.JumpToTask(data.currentlyCommandAddress + 1);
                    break;
                }
            }

            case I:
            {
                break;
            }

            default:
            {
                throw std::invalid_argument("invalid modefier");
            }

        }

    }


    std::string GetOperation() override
    {
        return std::string("SNE");
    };

};

namespace
{
  Instruction *create_SNE(const InstructionData &data) {
    return new Instr_SNE(data);
  }

  bool b = Factory::GetInstance()->RegisterFunction("SNE", create_SNE);
};
