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

public slots:
    void addCustomer();
private slots:
    void openContextualMenu(const QPoint point);
private:
    void updateTable();
    void updateTree();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
