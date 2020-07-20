#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QRandomGenerator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_generateBtn_clicked();

private:
    Ui::MainWindow *ui;
    QVector<QString> m_vecRandomData;
    QRandomGenerator    m_rRed;
    QRandomGenerator    m_rBlue;
};

#endif // MAINWINDOW_H
