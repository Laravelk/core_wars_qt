#pragma once

#include <iostream>
#include <string>

class ReadyDataForCommand;

enum TypeInstruction
{
    DAT,
    MOV,
    ADD,
    SUB,
    JMP,
    JMZ,
    DJZ,
    CMP
};

enum Mode
{
    IMMEDIATE, //#
    DIRECT, //$
    A_INDIRECT, //*
    B_INDIRECT, //@
    A_DECREMENT, //{
    B_DECREMENT, //<
    A_INCREMENT, //}
    B_INCREMENT //>
};

enum Modifier
{
    A,
    B,
    AB,
    BA,
    F,
    X,
    I
};

// !!!!!!!!!!!!
// clang-format
// !!!!!!!!!!!!

struct InstructionData {
    InstructionData(Mode ModeA_i, Mode ModeB_i, Modifier Modifier_i,
                    int AddrA_i, int AddrB_i):  ModeA(ModeA_i),ModeB(ModeB_i),
                                                ModifierData(Modifier_i),AddrA(AddrA_i),AddrB(AddrB_i){}
    InstructionData() = default;

    Mode ModeA;
    Mode ModeB;
    Modifier ModifierData;
    int AddrA;
    int AddrB;
};

class Instruction { //инструкция. общие операции, хранит некоторые данные
public:
    explicit Instruction(const InstructionData &instr_data): data(instr_data) {}
    //virtual ~Instruction();
    InstructionData get_data() const{return data;}
    void UpdateData(ReadyDataForCommand &data)const;

    virtual void Print()const = 0;
    virtual void RunInstruction(ReadyDataForCommand &data) = 0;
    virtual std::string GetOperation() = 0;

    void SetModeA(Mode a) {data.ModeA = a;}
    void SetModeB(Mode b) {data.ModeB = b;}
    void SetAddressA(int A) {data.AddrA = A;}
    void SetAddressB(int B) {data.AddrB = B;}

    Mode GetModeA() {return data.ModeA;}
    Mode GetModeB() {return data.ModeB;}
    int GetAddressA() {return data.AddrA;}
    int GetAddressB() {return data.AddrB;}
    Modifier GetModifier() {return data.ModifierData;}

private:
    InstructionData data;
};

//конкретная инструкция, с конкретной операцией. Instruction > InstructionData > ReadyInstruction

struct ReadyInstruction{
    explicit  ReadyInstruction(const std::string &iOperationCode = "DAT", Mode iModeA = IMMEDIATE, Mode iModeB = IMMEDIATE, Modifier iModefierData = F,
                     int iAddrA = 0, int iAddrB = 0):operationCode(iOperationCode),modeA(iModeA),modeB(iModeB),
                     modifierData(iModefierData),addrA(iAddrA),addrB(iAddrB){}
    ~ReadyInstruction() = default;

    std::string operationCode;
    Mode modeA;
    Mode modeB;
    Modifier modifierData;
    int addrA;
    int addrB;
};
