#include "Setting.h"

Setting::Setting(GameSettings *gs, QWidget *parent) : QWizardPage(parent),  gameSetting(gs)
{
    setTitle(tr("Game Setup"));

    //connect(loopCountSpinBox, &QSpinBox::valueChanged, this, &Setting::SetMaxLoopCount);
}

void Setting::SetMaxLoopCount()
{
    a1 = loopCountSpinBox->value();

}

void Setting::SetMaxWarriorCount()
{

}

void Setting::SetMaxTurnCount()
{

}

void Setting::SetMinDistance()
{

}

void Setting::SetCoreSize()
{

}
