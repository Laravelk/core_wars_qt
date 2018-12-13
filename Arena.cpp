#include "Arena.h"

Arena::Arena (QWidget *parent) : QWidget(parent)
{
    corePtr = nullptr;
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize Arena::minimumSizeHint() const
{
    return QSize(1600,800);
}

QSize Arena::sizeHint() const
{
    return QSize(800, 400);
}

void Arena::paintEvent(QPaintEvent *event)
{
    if(corePtr)
    {
        int widht = this->width();
        int height = this->height();

        int cellsNumber = corePtr->CORE_SIZE;

        int cellsInLine = widht / cellSize;
        int numberOfLines = cellsNumber / cellsInLine +
                ((cellsNumber % cellsInLine) ? 1 : 0);

        QPainter painter(this);

        for (int i = 0; i < cellsInLine; ++i)
        {
            painter.drawLine(i * cellSize, 0, i * cellSize, cellSize * numberOfLines);
        }

        for (int j = 0; j < cellsNumber; j++)
        {
            painter.drawLine(0, j*cellSize, cellsInLine * cellSize, j * cellSize);
        }
    }
}
