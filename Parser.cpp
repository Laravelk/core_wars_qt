#include "Parser.h"


WarData Parser::ParserWarData(std::ifstream &InputFile)
{
    WarData warData;
    warData.commandCounter = 0;
    warData.firstInstructionAddress = 0;

    for (std::string line; std::getline(InputFile,line);)
    {

        if (line.substr(0,3) == "ORG")
        {
            try
            {
                warData.firstInstructionAddress = std::stoi(line.substr(3));
            }
            catch(std::exception &)
            {
                throw std::invalid_argument("Impossible Start Address");
            }
        }
        else
        {
            warData.readyInstructionVector.push_back(ParserInstruction(line));
            warData.commandCounter++;
        }
    }
    return warData;
}

ReadyInstruction Parser::ParserInstruction(const std::string line)const
{
    std::string operationCode = line.substr(0,3);
    if(operationCode != "ADD" && //настроить для функций, которые будем добавлять в будущем. Выстроить ирархию
       operationCode != "MOV" &&
       operationCode != "DAT" &&
       operationCode != "SUB" &&
       operationCode != "JMP" &&
       operationCode != "JMZ" &&
       operationCode != "DJZ" &&
       operationCode != "CMP")
    {
        throw std::invalid_argument("We don't have this operation!");
    }


    Modifier commandModifier;
    std::size_t pointPos = 0;
    std::size_t spacePos = 0;
    if ((spacePos = line.find(' ')) == std::string::npos)
    {
        throw std::invalid_argument("Space after Modifire not found");
    }

    if ((pointPos = line.find('.')) != std::string::npos)
    {
        try
        {
            commandModifier = StrToModifier(line.substr(pointPos+1,spacePos-(pointPos + 1)));
        }
        catch(std::exception &)
        {
            throw std::invalid_argument("Impossible Modifier");
        }
    }

    //Zone Mode
    std::size_t commaPos = 0;
    if ((commaPos = line.find(',')) == std::string::npos)
    {
        throw std::invalid_argument("Comma is't found");
    }
    Mode modeA;

    try
    {
        modeA = StrToMode(line.substr(spacePos + 1, 1));
    }
    catch (std::exception &)
    {
        throw std::invalid_argument("modeA not found");
    }

    int addrA;
    try
    {
        addrA = std::stoi(line.substr(spacePos+2,commaPos - (spacePos + 2)));
    }
    catch(std::exception &)
    {
        throw std::invalid_argument("AddrA not found");
    }

    Mode modeB;
    try
    {
        modeB = StrToMode(line.substr(commaPos+2,1));
    }
    catch(std::exception &)
    {
        throw std::invalid_argument("ModeB not found");
    }

    std::size_t EndPos = line.length();
    int addrB;

    try
    {
        addrB = std::stoi(line.substr(commaPos + 3, EndPos));
    }
    catch(std::exception &)
    {
        throw std::invalid_argument("AddrB not found");
    }
    ReadyInstruction Data(operationCode,modeA,modeB,commandModifier,addrA,addrB);
    return Data;
}

Mode Parser::StrToMode(const std::string mode)const {
    if (mode == "#"){
        return IMMEDIATE;
    } else if(mode == "$"){
        return DIRECT;
    } else if(mode == "@") {
        return A_INDIRECT;
    } else if(mode == "*"){
        return B_INDIRECT;
    } else if(mode == ">"){
        return A_INCREMENT;
    } else if(mode == "}"){
        return B_INCREMENT;
    } else if(mode == "<"){
        return A_DECREMENT;
    } else if(mode == "{"){
        return B_DECREMENT;
    } else {
        throw std::exception();
    }
}

Modifier Parser::StrToModifier(const std::string modefier)const {
    if(modefier == "A"){
        return A;
    } else if(modefier == "B"){
        return B;
    } else if(modefier == "AB"){
        return AB;
    } else if(modefier == "BA"){
        return BA;
    } else if(modefier == "F"){
        return F;
    } else if(modefier == "X"){
        return X;
    } else if(modefier == "I"){
        return I;
    } else{
        throw std::exception();
    }
}
