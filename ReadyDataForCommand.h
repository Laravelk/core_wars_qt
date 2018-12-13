#pragma once

#include <iostream>

#include "Factory.h"
#include "Core.h"
#include "Warrior.h"
#include "Instruction.h"

class ReadyDataForCommand{
public:
    ReadyDataForCommand(Core *icore, Warrior *iwarrior) :
    core_(icore),warrior_(iwarrior),startAddress(iwarrior->firstWarriorAddress),
    currentlyCommandAddress(iwarrior->taskAddressWarriorVector.front()){}

    int GetCoreSize()
    {
        return core_->CORE_SIZE;
    }

    Instruction *GetAPtrForRead(){ //where A arg in out data
        return (*core_)[NRPA + currentlyCommandAddress];
    }

    Instruction *GetBPtrForRead(){ //where B arg in our data
        return (*core_)[NRPB + currentlyCommandAddress];
    }

    Instruction *GetAPtrForWrite(){ //where we want to change data. Arg A is address of this data
        return (*core_)[NWPA + currentlyCommandAddress];
    }

    Instruction *GetBPtrForWrite(){
        return (*core_)[NWPB + currentlyCommandAddress];
    }


    void Reset(int index, Instruction *instr){
        core_->Reset(index, instr);
    }

    void AddWarriorInGame(int index){
        warrior_->taskAddressWarriorVector.push_back(index);
    }

    void DeleteWarriorFromGame(){
        warrior_->taskAddressWarriorVector.clear();
    }

    void JumpToTask(int indexNewTask){
        warrior_->taskAddressWarriorVector.pop_front();
        warrior_->taskAddressWarriorVector.push_front(indexNewTask);
    }

    int startAddress;
    int currentlyCommandAddress;

    int NWPA; //new write pointer A
    int NWPB; //new write pointer B

    int NRPA; //new read pointer A
    int NRPB; //new read pointer B

private:
    Core *core_;
    Warrior *warrior_;
};
