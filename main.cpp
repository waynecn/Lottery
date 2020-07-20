#include "mainwindow.h"
#include "common.h"

#include <QApplication>
#include <QDateTime>
#include <QMutex>
#include <QFile>
#include <QTextStream>
#include <QDebug>

//用日志文件保存打印信息，供定位
void outputMessage(QtMsgType type, const QMessageLogContext &/*context*/, const QString &msg) {
    static QMutex mutex;
    mutex.lock();
    QString text;
    switch (type) {
    case QtDebugMsg: {
        text = "Debug:";
        break;
    }
    case QtWarningMsg: {
        text = "Warning:";
        break;
    }
    case QtCriticalMsg: {
        text = "Critical:";
        break;
    }
    case QtFatalMsg: {
        text = "Fatal:";
        break;
    }
    default: {
        text = "Info:";
        break;
    }
    }

    QString curDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString curTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString message = QString("%1 %2 %3").arg(curTime).arg(text).arg(msg);

    if (!APPLICATION_DIR.isEmpty()) {
        QString logFile(APPLICATION_DIR + QString("/AnalyseECG_%1.log").arg(curDate));
        QFile file(logFile);
        file.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream tStream(&file);
        tStream << message << "\r\n";
        file.flush();
        file.close();
    }
    mutex.unlock();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    APPLICATION_DIR = QCoreApplication::applicationDirPath();

#ifdef QT_NO_DEBUG
    qInstallMessageHandler(outputMessage);
#else
    qDebug() << "DEBUG TYPE";
#endif

    MainWindow w;
    w.show();

    return a.exec();
}
