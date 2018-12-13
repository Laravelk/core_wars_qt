#ifndef SETTING_H
#define SETTING_H

#include <QWizardPage>
#include <QSpinBox>
#include <QWidget>

#include <Mars.h>
#include <Parser.h>
#include <Mars.h>

//данный класс заполняет GameSettings
//он же парсит redcode

class QLabel;
class QSpinBox;

class Setting : public QWizardPage
{
Q_OBJECT

public:
    Setting(GameSettings *gs, QWidget *parent = 0);

private slots:
    void SetMaxLoopCount();
    void SetMaxWarriorCount();
    void SetMaxTurnCount();
    void SetMinDistance();
    void SetCoreSize();

private:
    int CheckGameData();

    int a1;

    QLabel *loopCountLabel;
    QLabel *warriorCountLabel;
    QLabel *turnCountLabel;
    QLabel *minDistanceLabel;
    QLabel *coreSizeLabel;

    QSpinBox *loopCountSpinBox;



    const int minWarriorCount = 2;
    const int minTurnCount = 0;

    GameSettings *gameSetting;

};

#endif // SETTING_H
