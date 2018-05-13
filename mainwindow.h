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
    void displaySizeBox(bool);
    void changingColor(bool);
    void untoggleBoxFunc(bool);

public slots:
    void addEllipse(bool toggled);
    void addLine(bool toggled);
    void addRectangle(bool toggled);
    void changingSize(bool triggered);
    void changedColor(bool triggered);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
