#include "Instruction.h"
#include "ReadyDataForCommand.h"

void Instruction::UpdateData(ReadyDataForCommand &ready_data)const {

    //Zone A

    if (data.ModeA == IMMEDIATE) { //число, которое стоит за этим номером уже является нужным нам адресом
        ready_data.NRPA = 0;
        ready_data.NWPA = 0;
    }
    else
    {
        ready_data.NRPA = data.AddrA;
        ready_data.NWPA = data.AddrA;
    }

    if (data.ModeA == A_INDIRECT){
        //
    }


    //Zone B

    if (data.ModeB == IMMEDIATE){
        ready_data.NRPB = 0;
        ready_data.NWPB = 0;
    }
    else
    {
        ready_data.NRPB = data.AddrB;
        ready_data.NWPB = data.AddrB;
    }

    if (data.ModeB == A_INDIRECT){
        //
    }
}
