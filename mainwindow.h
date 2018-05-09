#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void addingEllipse(bool);
    void addingLine(bool);
    void addingRectangle(bool);

public slots:
    void addEllipse(bool toggled);
    void addLine(bool toggled);
    void addRectangle(bool toggled);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
