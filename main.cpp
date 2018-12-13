#include "mainwindow.h"
#include <QApplication>
#include <QLabel>

#include <Mars.h>
#include <Parser.h>

void StartExGame()
{
    std::string w1("C:\\Users\\Laravelk\\CLionProjects\\core_wars\\w1.txt");

        std::ifstream ifs;

        WarData WarData1;
        WarData WarData2;

        ifs.open(w1);
        WarData1 = Parser::GetInstance()->ParserWarData(ifs);
        WarData1.warName = "w1";
        ifs.close();

        std::string w2("C:\\Users\\Laravelk\\CLionProjects\\core_wars\\w2.txt");

        ifs.open(w2);
        WarData2 = Parser::GetInstance()->ParserWarData(ifs);
        WarData2.warName = "w2";
        ifs.close();

        ReadyInstruction defInstr;

        GameSettings gs;
        gs.maxLoopCount = 300;
        gs.coreSize = 15;
        gs.maxTurnCount = 100;
        gs.maxWarriorCount = 2;
        gs.minDistance = 5;
        gs.defaultInstruction = defInstr;
        gs.warDataVector.push_back(WarData1);
        gs.warDataVector.push_back(WarData2);

        mars game_mars(gs);
        game_mars.StartTheGame();
        while(game_mars.StatusGame() == INGAME)
        {
            game_mars.Turn();
        }

        if (game_mars.StatusGame() == HAVE_WINNER) {
            std::cout << "WINNER IS " << game_mars.ReturnWinnerName() << std::endl;
        }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Setting s;
    s.show();
    //MainWindow w;
    //w.show();

    return a.exec();
}
