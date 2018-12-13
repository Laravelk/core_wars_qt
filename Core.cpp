#include "Core.h"

void Core::LoadInstruction(const ReadyInstruction &instr, int index)
{
    if (index < 0)
    {
        throw std::invalid_argument("index < 0");
    }   
    coreMemory_[index % CORE_SIZE].reset(Factory::GetInstance()->create(instr.operationCode,InstructionData(instr.modeA,
                                                                        instr.modeB,instr.modifierData,instr.addrA,instr.addrB)));
}

void Core::Reset(int index, Instruction *instr) {
    coreMemory_[index % CORE_SIZE].reset(instr);
}


Instruction *Core::operator[](int index)
{
    return coreMemory_[index % CORE_SIZE].get();
}

void Core::Print() const {
    for (int i = 0; i < CORE_SIZE; i++)
    {
        coreMemory_[i].get()->Print();
        std::cout << " ";
    }
    std::cout << "\n";
}
