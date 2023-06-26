#include <time.h>

#include "UTimer.h"
//#include "SLogger.h"
#include "UInteraction.h"
#include "FThreads.h"
#include "UProcess.h"
#include "UTask.h"

#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    signal(SIGINT, SigintHandler_v);

    Interaction Args_o(argc, argv);

//    LogRegistration(QString::fromStdString(Args_o.LogFile));
//    qInfo() << "------ START ------";

    Process* Process_po = new Process(Args_o.GetPID_i()); // создание + предсчитывание

    CreateThreads_v(Args_o.GetThreadsCount_i(), Process_po, Args_o.GetOutputFile_str()); // передача объекта процесса в потоки считывания

    Timer Timer_o;
    Timer_o.StartTimer_v(Args_o.GetDelta_i(), Args_o.GetCount_i());

    fprintf(stdout, "Конец! AAAAAAAAAA");

    return 0;
}
