#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton->setStyleSheet(g_strRedBtnStyleSheet);
    ui->pushButton_2->setStyleSheet(g_strRedBtnStyleSheet);
    ui->pushButton_3->setStyleSheet(g_strRedBtnStyleSheet);
    ui->pushButton_4->setStyleSheet(g_strRedBtnStyleSheet);
    ui->pushButton_5->setStyleSheet(g_strRedBtnStyleSheet);
    ui->pushButton_6->setStyleSheet(g_strRedBtnStyleSheet);
    ui->pushButton_7->setStyleSheet(g_strBlueBtnStyleSheet);

    quint32 nRedStart = 1, nRedEnd = 32, nBlueStart = 1, nBlueEnd = 16;
    m_rRed = QRandomGenerator(&nRedStart, &nRedEnd);
    m_rBlue = QRandomGenerator(&nBlueStart, &nBlueEnd);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateBtn_clicked()
{
    qDebug() << "on_generateBtn_clicked";
    m_vecRandomData.clear();
    while (true) {
        quint32 ret = m_rRed.generate() % 32;
        if (ret == 0) {
            continue;
        }
        QString strRet = QString::asprintf("%02d", ret);
        if (m_vecRandomData.indexOf(strRet) != -1) {
            continue;
        }
        qDebug() << "ret:" << strRet;
        m_vecRandomData.push_back(strRet);
        if (m_vecRandomData.size() >= 6) {
            break;
        }
    }

    qSort(m_vecRandomData.begin(), m_vecRandomData.end());

    while (true) {
        quint32 ret = m_rBlue.generate() % 16;
        if (ret == 0) {
            continue;
        }
        QString strRet = QString::asprintf("%02d", ret);
        qDebug() << "ret:" << strRet;
        m_vecRandomData.push_back(strRet);
        break;
    }

    ui->pushButton->setText(m_vecRandomData[0]);
    ui->pushButton_2->setText(m_vecRandomData[1]);
    ui->pushButton_3->setText(m_vecRandomData[2]);
    ui->pushButton_4->setText(m_vecRandomData[3]);
    ui->pushButton_5->setText(m_vecRandomData[4]);
    ui->pushButton_6->setText(m_vecRandomData[5]);
    ui->pushButton_7->setText(m_vecRandomData[6]);
}
