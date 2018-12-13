#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>

#include "Arena.h"
#include "setting.h"

class QAction;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void StartGame();
   // void AddWarrior();
    //void Exit();
    //void AddSettigns();

private:
    void CreateAction();

private:
    bool gamePaused;
    bool settingsAdded;

    QAction *startGameAction;
    QAction *addWarrirorAction;
    QAction *exitAction;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
