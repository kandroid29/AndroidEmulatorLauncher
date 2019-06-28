#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ClickButton();

private:
    Ui::MainWindow *ui;
    QStringListModel *model;
    QStringList List;

    void getAndroidEmulators();
};

#endif // MAINWINDOW_H
