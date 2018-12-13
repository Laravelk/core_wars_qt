#pragma once

#include <iostream>
#include <list>

struct Warrior
{
    Warrior(std::string name, int start_address):
            warriorName(name),firstWarriorAddress(start_address){}

    std::string warriorName;
    int firstWarriorAddress;
    std::list <int> taskAddressWarriorVector; //возможно, можно заменить на простую переменную
};
