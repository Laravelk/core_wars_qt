#include "Instruction.h"
#include "Core.h"
#include "Mars.h"
#include "Factory.h"
class Instr_STL : public Instruction
{
public:
    Instr_STL(const InstructionData &data) : Instruction(data){}

    void Print()const override
    {
        std::cout << "STL";
    }

    std::string GetOperation() override
    {
        return std::string("STL");
    };

    void RunInstruction(ReadyDataForCommand &data) override //if a < b -> skip instr
    {
        UpdateData(data);

        switch(GetModifier())
        {
            case A:
            {
                if (data.GetAPtrForRead()->GetAddressA() < data.GetBPtrForRead()->GetAddressA())
                {
                    data.JumpToTask((data.currentlyCommandAddress + 1) % data.GetCoreSize());                }
                break;
            }

            case B:
            {
                if (data.GetAPtrForRead()->GetAddressA() < data.GetBPtrForRead()->GetAddressA())
                {
                    data.JumpToTask(data.currentlyCommandAddress + 1);
                }
                break;
            }

            case AB:
            {
                if (data.GetAPtrForRead()->GetAddressA() < data.GetBPtrForRead()->GetAddressB())
                {
                    data.JumpToTask((data.currentlyCommandAddress + 1) % data.GetCoreSize());                }
                break;
            }

            case BA:
            {
                if (data.GetAPtrForRead()->GetAddressB() < data.GetBPtrForRead()->GetAddressA())
                {
                    data.JumpToTask((data.currentlyCommandAddress + 1) % data.GetCoreSize());                }
                break;
            }

            case F:
            {
                if ((data.GetAPtrForRead()->GetAddressA() < data.GetBPtrForRead()->GetAddressA()) &&
                    (data.GetAPtrForRead()->GetAddressB() < data.GetBPtrForRead()->GetAddressB()))
                {
                    data.JumpToTask((data.currentlyCommandAddress + 1) % data.GetCoreSize());
                    break;
                }
            }

            case X:
            {
                if ((data.GetAPtrForRead()->GetAddressA() < data.GetBPtrForRead()->GetAddressB()) &&
                    (data.GetAPtrForRead()->GetAddressB() < data.GetBPtrForRead()->GetAddressA()))
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
};

namespace
{
  Instruction *create_STL(const InstructionData &data){
      return new Instr_STL(data);
  }

  bool b = Factory::GetInstance()->RegisterFunction("STL", create_STL);
};
