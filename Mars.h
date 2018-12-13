#pragma once

#include <vector>
#include <list>
#include <random>

#include "Core.h"
#include "Instruction.h"
#include "Warrior.h"
#include "ReadyDataForCommand.h"

struct WarData
{
    WarData(int first_instruction, size_t counter_command):
            firstInstructionAddress(first_instruction), commandCounter(counter_command){}
    WarData() = default;


    std::string warName;
    std::vector <ReadyInstruction> readyInstructionVector;
    int firstInstructionAddress;
    std::size_t	commandCounter;
};


struct GameSettings
{
    GameSettings(int max_loop, int warrior_count, int max_turn, int core_s, ReadyInstruction &defInstr,
                int min_distance):
                maxLoopCount(max_loop), maxWarriorCount(warrior_count), maxTurnCount(max_turn), coreSize(core_s),
                defaultInstruction(defInstr), minDistance(min_distance){}

    GameSettings() = default;

    ReadyInstruction defaultInstruction;
    int maxLoopCount;
    int maxWarriorCount;
    int maxTurnCount;
    int minDistance;
    int coreSize;
    std::vector<WarData> warDataVector;
};

enum GameStatus{PREPARE,INGAME,PAUSE,END,HAVE_WINNER};

class mars
{
public:
mars(GameSettings gs);

void AddWarriorInGame(WarData war_data);
void Turn();
void StartTheGame();

GameStatus StatusGame()
{
    return gameStatus;
};

std::string ReturnWinnerName()
{
    return warriorVector_.front().warriorName;
};

private:
Core coreMars_;
std::vector<Warrior>::iterator currentlyWarriorIt_;
std::vector<Warrior> warriorVector_;
std::size_t countLoop;

GameStatus gameStatus;
const int MAX_COUNT_LOOP_;
const int MAX_WARRIOR_COUNT_;
const int MIN_DISTANCE_;

};
