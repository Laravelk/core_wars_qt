#include "Mars.h"

mars::mars(GameSettings gs): coreMars_(gs.coreSize, gs.defaultInstruction), MAX_WARRIOR_COUNT_(gs.maxWarriorCount),
                             gameStatus(PREPARE), MAX_COUNT_LOOP_(gs.maxLoopCount), countLoop(0), MIN_DISTANCE_(gs.minDistance)
{

    for (std::size_t i = 0; i < MAX_WARRIOR_COUNT_; i++)
    {
        WarData a = gs.warDataVector[i];
      AddWarriorInGame(gs.warDataVector[i]);
    }
    std::cout << "START MEMORY: ";
    coreMars_.Print();
    currentlyWarriorIt_ = warriorVector_.begin();
}


void mars::AddWarriorInGame(WarData war_data) {

    if (MAX_WARRIOR_COUNT_ == warriorVector_.size()) {
        throw std::invalid_argument("warrior vector is full");
    }

    static const int MemoryForOneWarrior = coreMars_.CORE_SIZE / MAX_WARRIOR_COUNT_;

    std::random_device rd;
    std::mt19937_64 gen(rd());

    int RandomPlace;

    if (!warriorVector_.empty())
    {
      //std random shafl
      //Алгоритм Фишера Яца

        /*
    std::size_t firstFreePosition = ( (warList.empty()) ? 0 : (warList.back().firstInstructionAddress + MIN_DISTANCE) );

        std::uniform_int_distribution<std::size_t> dis(firstFreePosition,
                           sectorSize * (warList.size() + 1) - warData.instructionList.size());
        positionToPlace = dis(gen);

    } else {
        positionToPlace = ( (warList.empty()) ? 0 : (warList.back().firstInstructionAddress + SEPARATION) );
}
        */
        int firstFreePosition = ( (warriorVector_.empty()) ? 0 : (warriorVector_.back().firstWarriorAddress + MIN_DISTANCE_) );
        std::uniform_int_distribution<int> d(firstFreePosition,
                                             MemoryForOneWarrior * (warriorVector_.size() + 1) - war_data.readyInstructionVector.size());
        RandomPlace = d(gen);
    }
    else
    {
        RandomPlace = 0;
    }


    int i = RandomPlace;
    std::vector <ReadyInstruction>::iterator it;
    for (it = war_data.readyInstructionVector.begin(); it != war_data.readyInstructionVector.end(); ++it){
        coreMars_.LoadInstruction(*it, i % coreMars_.CORE_SIZE);
        ++i;
    }

    warriorVector_.emplace_back(war_data.warName, war_data.firstInstructionAddress + RandomPlace);
    warriorVector_.back().taskAddressWarriorVector.push_back(RandomPlace + war_data.firstInstructionAddress);
    return;
}

void mars::Turn() {
    if (warriorVector_.size() == 1)
    {
        gameStatus = HAVE_WINNER;
        return;
    }

    if (currentlyWarriorIt_ == warriorVector_.end())
    {
        if (countLoop == MAX_COUNT_LOOP_)
        {
            gameStatus = END;
            return;
        }
        else
        {
            countLoop++;
        }

        currentlyWarriorIt_ = warriorVector_.begin(); //если каждый warrior сделал свой ход
    }

    int address_currently_task = currentlyWarriorIt_->taskAddressWarriorVector.front();

    ReadyDataForCommand Command(&coreMars_,&(*currentlyWarriorIt_));
    currentlyWarriorIt_->taskAddressWarriorVector.push_back(currentlyWarriorIt_->taskAddressWarriorVector.front() + 1);
    currentlyWarriorIt_->taskAddressWarriorVector.pop_front();
    coreMars_[address_currently_task]->RunInstruction(Command);

    if (currentlyWarriorIt_->taskAddressWarriorVector.empty())
    {
        std::vector<Warrior>::iterator tmp_it;
        tmp_it = currentlyWarriorIt_;
        std::cout << "it's turn is " << currentlyWarriorIt_->warriorName << "\n";
        std::cout << "address command is " << address_currently_task << ":\n";

        coreMars_.Print();
        std::cout << "\n";
        currentlyWarriorIt_++;

        warriorVector_.erase(tmp_it); //надо бы еще занулить все функции данного бойца
        return;
    }

    std::cout << "it's turn is " << currentlyWarriorIt_->warriorName << "\n";
    std::cout << "address command is " << address_currently_task << ":\n";

    coreMars_.Print();
    std::cout << "\n";
    currentlyWarriorIt_++;
    return;
}

void mars::StartTheGame()
{
    gameStatus = INGAME;
}
