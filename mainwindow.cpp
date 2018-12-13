#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    gamePaused = true;

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateAction()
{
    startGameAction = new QAction(tr("&New Game"), this);
    startGameAction->setStatusTip(tr("Start New Game"));
    startGameAction->setShortcut(tr("Ctrl+N"));
    connect(startGameAction,SIGNAL(triggered()),this, SLOT(StartGame));
}

void MainWindow::StartGame()
{

}
