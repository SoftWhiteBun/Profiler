#include "Logger.h"

#include <QDebug>
#include <QFile>
#include <QDir>
#include <QScopedPointer>
#include <QTextStream>
#include <QDateTime>

QScopedPointer<QFile> LogFile;

void MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QTextStream OStream_o(LogFile.data());
    const char * FileName_pcc = context.file ? context.file : "";
    const char * FunctionName_pcc = context.function ? context.function : ""; // ---------------------разобраться подробнее
    QString DateTime_Str = QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss.zzz] ");
    switch (type) {
    case QtDebugMsg:
      OStream_o << "      DD >> "<<DateTime_Str;
      break;
    case QtInfoMsg:
      OStream_o << "      II >> "<<DateTime_Str;
      break;
    case QtWarningMsg:
      OStream_o << "    WW >> "<<DateTime_Str;
      break;
    case QtCriticalMsg:
      OStream_o << "  EE >> "<<DateTime_Str << " "<< FileName_pcc<<":"<< context.line <<"->"<< FunctionName_pcc;
      break;
    case QtFatalMsg:
      OStream_o << "FF >> "<<DateTime_Str << " "<< FileName_pcc<<":"<<context.line <<"->"<< FunctionName_pcc;
      break;
    }

    OStream_o << ": " << msg << endl; // Записываем в вывод категорию сообщения и само сообщение
    OStream_o.flush();    // Очищаем буферизированные данные
}

void CheckDuplicateFilenames(QString Filename) {

    if (QFile::exists(Filename)) {
        int i = 1;
        QString TempFilename = Filename;
        do {
            if (Filename != TempFilename) Filename = TempFilename;
            Filename = QString("%1(%2)").arg(Filename).arg(i);
            i++;
        } while (QFile::exists(Filename));
    }
}

bool SetLogFile(QString Filename = "") {
    bool IsOk = false;
    if (Filename == "") { //-------------если файл не задан
        //запись в поток вывода (?) и в файл по умолчанию с расположением по умолчанию
        QString DateTime = QDateTime::currentDateTime().toString("Log_dd.MM.yyyy_HH:mm:ss");
        CheckDuplicateFilenames(Filename);

        LogFile.reset(new QFile(DateTime));// Устанавливаем файл логирования,
        LogFile.data()->open(QFile::Append | QFile::Text);// Открываем файл логирования
        IsOk = true;
    }

    else {
        CheckDuplicateFilenames(Filename);

        LogFile.reset(new QFile(Filename));// Устанавливаем файл логирования,
        LogFile.data()->open(QFile::Append | QFile::Text);// Открываем файл логирования
        IsOk = true;
    }
    return IsOk;
}

void LogRegistration(QString Filename)
{
  if (SetLogFile(Filename) == true ) {
    qInstallMessageHandler(MessageHandler);
  }
}
