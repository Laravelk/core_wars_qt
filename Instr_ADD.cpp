#include "Instruction.h"
#include "Core.h"
#include "Mars.h"
#include "Factory.h"
class Instr_ADD : public Instruction
{
public:
    Instr_ADD(const InstructionData &idata) : Instruction(idata) {}

    void Print()const override
    {
        std::cout << "ADD";
    }

    void RunInstruction(ReadyDataForCommand &data) override
    {
        UpdateData(data);
        switch (GetModifier()) {
            case A:
                {
                data.GetBPtrForRead()->SetAddressA(
                        (data.GetAPtrForRead()->GetAddressA() + data.GetBPtrForRead()->GetAddressA()) %
                            data.GetCoreSize());
                break;
                }
            case B:
                {
                    data.GetBPtrForWrite()->SetAddressB(
                        (data.GetAPtrForRead()->GetAddressB() + data.GetBPtrForRead()->GetAddressB()) %
                            data.GetCoreSize());
                break;
                }
            case AB:
                {
                //Instruction *test = data.GetBPtrForWrite();
                //Instruction *test2 = data.GetAPtrForRead();
                    data.GetBPtrForWrite()->SetAddressB(
                        (data.GetAPtrForRead()->GetAddressA() + data.GetBPtrForRead()->GetAddressB()) %
                            data.GetCoreSize());
                break;
                }
            case BA:
                {
                data.GetBPtrForWrite()->SetAddressA(
                        (data.GetAPtrForRead()->GetAddressB() + data.GetBPtrForRead()->GetAddressA()) %
                            data.GetCoreSize());
                break;
                }
            case F:
            case I:
                {
                data.GetBPtrForWrite()->SetAddressA(
                        (data.GetAPtrForRead()->GetAddressA() + data.GetBPtrForRead()->GetAddressA()) %
                            data.GetCoreSize());
                    data.GetBPtrForWrite()->SetAddressB(
                        (data.GetAPtrForRead()->GetAddressA() + data.GetBPtrForRead()->GetAddressB()) %
                            data.GetCoreSize());
                break;
                }
            case X: {
                data.GetBPtrForWrite()->SetAddressA(
                        (data.GetAPtrForRead()->GetAddressB() + data.GetBPtrForRead()->GetAddressA()) %
                            data.GetCoreSize());
                data.GetBPtrForWrite()->SetAddressB(
                    (data.GetAPtrForRead()->GetAddressA() + data.GetBPtrForRead()->GetAddressB()) %
                        data.GetCoreSize());
                break;
                }
            default:
                throw std::invalid_argument("invalid modifier");
        }
    };

    std::string GetOperation() override
    {
        return std::string("ADD");
    };
};

namespace
{
    Instruction *create_ADD(const InstructionData &idata)
    {
        return new Instr_ADD(idata);
    }


    bool b = Factory::GetInstance()->RegisterFunction("ADD", create_ADD);
}
