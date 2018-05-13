#include "mainwindow.h"
#include "imageview.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->layout()->addWidget(new ImageView(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addEllipse(bool toggled)
{
    emit addingEllipse(toggled);
}


void MainWindow::addLine(bool toggled)
{
    emit addingLine(toggled);
}

void MainWindow::addRectangle(bool toggled)
{
    emit addingRectangle(toggled);
}

void MainWindow::changingSize(bool triggered)
{
    emit displaySizeBox((triggered));
    emit untoggleBoxFunc(false); // have to wire
}

void MainWindow::changedColor(bool triggered)
{
    emit changingColor(triggered);
    emit untoggleBoxFunc(false);
}
