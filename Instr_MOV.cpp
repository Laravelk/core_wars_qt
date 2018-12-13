#include "Instruction.h"
#include "Core.h"
#include "Mars.h"
#include "Factory.h"

class Instr_MOV : public Instruction
{
public:
    Instr_MOV(const InstructionData &idata): Instruction(idata){}

    void Print()const override{
        std::cout << "MOV";
    }

    void RunInstruction(ReadyDataForCommand &data)override
    {

        UpdateData(data);
        switch(GetModifier())
        {
            case A:
            {
                data.GetBPtrForWrite()->SetAddressA(data.GetAPtrForRead()->GetAddressA());
                break;
            }

            case B:
            {
                data.GetBPtrForWrite()->SetAddressB(data.GetBPtrForRead()->GetAddressB());
                break;
            }

            case AB:
            {
                data.GetBPtrForWrite()->SetAddressB(data.GetAPtrForRead()->GetAddressA());
                break;
            }

            case BA:
            {
                data.GetAPtrForWrite()->SetAddressA(data.GetBPtrForRead()->GetAddressB());
                break;
            }

            case F:
            {
                data.GetBPtrForWrite()->SetAddressA(GetAddressB());
                data.GetAPtrForWrite()->SetAddressB(GetAddressA());
                break;
            }

            case X:
            {
                data.GetBPtrForWrite()->SetAddressB(GetAddressA());
                data.GetAPtrForRead()->SetAddressA(GetAddressB());
                break;
            }

            case I:
            {
                //Instruction *test = data.GetAPtrForRead();
                //InstructionData test2 = get_data();
                data.Reset((data.NWPB + data.currentlyCommandAddress) % data.GetCoreSize(), Factory::GetInstance()
                    ->create(data.GetAPtrForRead()->GetOperation(), get_data()));
                break;
            }

            default:
                throw std::invalid_argument("invalid modifier");
        }
    }

    std::string GetOperation() override
    {
        return std::string("MOV");
    };
};


namespace
{
    Instruction *create_MOV(const InstructionData &idata)
    {
        return new Instr_MOV(idata);
    }

    bool b = Factory::GetInstance()->
        RegisterFunction("MOV", create_MOV);
}
