#ifndef ARENA_H
#define ARENA_H

#include <QWidget>
#include <QSize>
#include <QPainter>
#include "Core.h"

class Arena : public QWidget
{
Q_OBJECT

public:
    Arena(QWidget *parent = 0);

    void paintEvent(QPaintEvent *event)override;

    QSize minimumSizeHint()const override;
    QSize sizeHint()const override;

private:
    Core *corePtr;

    const int cellSize = 14;
};

#endif // ARENA_H
