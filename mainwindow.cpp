#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "common.h"

#include <QDebug>
#include <QTime>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->dateLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss "));
    ui->historyTable->setColumnCount(2);
    ui->historyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList headLabels;
    headLabels << "日期" << "号码";
    ui->historyTable->setHorizontalHeaderLabels(headLabels);
    ui->historyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->pushButton->setStyleSheet(g_strRedBtnStyleSheet);
    ui->pushButton_2->setStyleSheet(g_strRedBtnStyleSheet);
    ui->pushButton_3->setStyleSheet(g_strRedBtnStyleSheet);
    ui->pushButton_4->setStyleSheet(g_strRedBtnStyleSheet);
    ui->pushButton_5->setStyleSheet(g_strRedBtnStyleSheet);
    ui->pushButton_6->setStyleSheet(g_strRedBtnStyleSheet);
    ui->pushButton_7->setStyleSheet(g_strBlueBtnStyleSheet);

    m_rRed = QRandomGenerator(QTime(0,0,0).secsTo(QTime::currentTime()));
    m_rBlue = QRandomGenerator(QTime(0,0,0).secsTo(QTime::currentTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateBtn_clicked()
{
    ui->dateLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss "));
    QFile file(APPLICATION_DIR + "/" + g_strLotteryFileName);
    int nRow = 1;
    QVector<QStringList> vecItems;
    if (file.exists()) {
        //文件存在则打开 并展示到界面中
        file.open(QIODevice::ReadOnly);
        while (true) {
            QByteArray buf = file.readLine();
            if (buf.isNull()) {
                break;
            }
            QString strResults(buf);
            QString findStr = "Lottery Results:";
            int index = strResults.indexOf(findStr);
            if (index != -1) {
                QString strDate = strResults.mid(0, index - 1);
                QString lotteryResults = strResults.mid(index + findStr.length(), strResults.length() - index - 2);

                QStringList strList;
                strList << strDate << lotteryResults;
                vecItems.push_back(strList);

                nRow++;
            }
        }

        file.close();
    }

    ui->historyTable->clearContents();
    QStringList headLabels;
    headLabels << "日期" << "号码";
    ui->historyTable->setHorizontalHeaderLabels(headLabels);
    ui->historyTable->setRowCount(nRow - 1);
    for (int i = 0; i < vecItems.size(); ++i) {
        QStringList &list = vecItems[i];
        QString strDate = list[0];
        QString lotteryResults = list[1].trimmed();
        QTableWidgetItem *item = new QTableWidgetItem(strDate);
        QTableWidgetItem *item2 = new QTableWidgetItem(lotteryResults);
        ui->historyTable->setItem(i, 0, item);
        ui->historyTable->setItem(i, 1, item2);
    }

    qDebug() << "on_generateBtn_clicked";
    m_vecRandomData.clear();
    while (true) {
        quint32 ret = m_rRed.generate() % 34;
        if (ret == 0) {
            continue;
        }
        QString strRet = QString::asprintf("%02d", ret);
        if (m_vecRandomData.indexOf(strRet) != -1) {
            continue;
        }
        m_vecRandomData.push_back(strRet);
        if (m_vecRandomData.size() >= 6) {
            break;
        }
    }

    qSort(m_vecRandomData.begin(), m_vecRandomData.end());

    while (true) {
        quint32 ret = m_rBlue.generate() % 17;
        if (ret == 0) {
            continue;
        }
        QString strRet = QString::asprintf("%02d", ret);
        m_vecRandomData.push_back(strRet);
        break;
    }

    qDebug() << "Lottery results:" << m_vecRandomData[0] << " " << m_vecRandomData[1] << " " << m_vecRandomData[2] << " "
             << m_vecRandomData[3] << " " << m_vecRandomData[4] << " " << m_vecRandomData[5] << " " << m_vecRandomData[6];

    ui->pushButton->setText(m_vecRandomData[0]);
    ui->pushButton_2->setText(m_vecRandomData[1]);
    ui->pushButton_3->setText(m_vecRandomData[2]);
    ui->pushButton_4->setText(m_vecRandomData[3]);
    ui->pushButton_5->setText(m_vecRandomData[4]);
    ui->pushButton_6->setText(m_vecRandomData[5]);
    ui->pushButton_7->setText(m_vecRandomData[6]);

    //写入结果
    QFile writeFile(APPLICATION_DIR + "/" + g_strLotteryFileName);
    //文件存在则打开 并展示到界面中
    writeFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&writeFile);
    ts << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ") << "Lottery Results:" << m_vecRandomData[0] << " " << m_vecRandomData[1] << " " << m_vecRandomData[2] << " "
       << m_vecRandomData[3] << " " << m_vecRandomData[4] << " " << m_vecRandomData[5] << " " << m_vecRandomData[6] << "\r\n";
    writeFile.flush();
    writeFile.close();
}
