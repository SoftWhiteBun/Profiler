#include "FThreads.h"

#include <signal.h>
#include <unistd.h>
//#include <string>
#include <pthread.h>

//#include "SLogger.h"
#include "CThreadConstants.h"
#include "UProcess.h"
#include "CConstants.h"
#include "UProcessDoubleBuffer.h"


void* ThreadRead_v(void* args)
{
    while (!IsExit_eb) {
        pthread_mutex_lock(&MutexRead_eo);
        pthread_cond_wait(&CondRead_eo, &MutexRead_eo);
        pthread_mutex_unlock(&MutexRead_eo);
        ArgThreadRead* _threadArg = (ArgThreadRead*) args;

        // если поток последний, то чтение информации о Процессе
        if (_threadArg->_IsLastThread_b)
            _threadArg->_Process_po->ReadDataFromStatFile_v();

        // чтение информации о подопечных Тасках
        _threadArg->_Process_po->ReadTasksForThread_v( _threadArg->_IndexThread_i, TimerTicks_eui.load() );

    }
    pthread_exit(0);
}

void* ThreadTasksCount_v(void* args)   // пересчет кол-ва потоков
{
    //fprintf(stdout, "вход\n");
    bool isFirstCall = true;
    while (!IsExit_eb) {
        pthread_mutex_lock(&MutexCountWait_eo);
        pthread_cond_wait(&CondCount_eo, &MutexCountWait_eo);
        pthread_mutex_unlock(&MutexCountWait_eo);

        ArgThreadTasksCount* _threadArg = (ArgThreadTasksCount*) args;
        Process* _Process = _threadArg->_Process_po;
        int ThreadsCount = _threadArg->_ThreadsCount_i;

        int previosTaskCount = _Process->GetTasksCount_i();

        pthread_mutex_lock(&MutexCountResize_eo);
        _Process->ReCountTasks_v();
        pthread_mutex_unlock(&MutexCountResize_eo);

        int nextTaskCount = _Process->GetTasksCount_i();

        if (previosTaskCount != nextTaskCount || isFirstCall) {

            _Process->ClearMatrix_v();

            int taskPerThread = nextTaskCount / ThreadsCount;
            int extraThread = nextTaskCount % ThreadsCount;

            int start = 0;
            for (int i = 0; i < ThreadsCount; ++i) {
                int end = start + taskPerThread;
                if (i < extraThread)
                    ++end;
                for (int j = start; j < end; ++j) {
                    _Process->PushElemToMatrix_v(i, j);
                }
                start = end;
            }
            isFirstCall = false;
        }
    }
    pthread_exit(0);
}

void* ThreadWrite_v(void* args)     //поток записи в файл
{
    FILE * fp = nullptr;
    ArgThreadWrite* ThreadArg = (ArgThreadWrite*) args;
    ProcessDoubleBuffer& DoubleBuffer = ProcessDoubleBuffer::GetInstance_rso();

    while (!IsExit_eb) {

        pthread_mutex_lock(&MutexWrite_eo);
        pthread_cond_wait(&CondCount_eo, &MutexWrite_eo);
        pthread_mutex_unlock(&MutexWrite_eo);

        unsigned char* WriteBuffer = DoubleBuffer.GetBufferToWrite_puc();
        unsigned int SavedPosition = DoubleBuffer.GetSavedPosition_ui();
        DoubleBuffer.ResetSavedPosition_v(); // == 0

        if (SavedPosition > 0) {
            const char * FileName = ThreadArg->_OutputFile_str.c_str();
            fp = fopen(FileName, "a");
            if (fp == nullptr) {
                exit(-2);
            }
            fwrite(WriteBuffer, SavedPosition, 1, fp);
            fclose(fp);
        }
    }

    if ((fp = fopen((const char *)&ThreadArg->_OutputFile_str, "a")) != nullptr) {
        unsigned char* LastBuffer = DoubleBuffer.GetCurrentBuffer_puc();
        unsigned int Position = DoubleBuffer.GetPosition_ui();
        fwrite(LastBuffer, Position, 1, fp);
        fclose(fp);
    }
}

// Обработчик выхода ^C
void SigintHandler_v (int /*signo*/)
{
    IsExit_eb = true;
    sleep(1);
}

void CreateThreads_v(int ThreadsCount, Process* _Process, std::string OutputFile)
{

    if (ThreadsCount > (sysconf(_SC_STREAM_MAX) - 3)) {
        //qInfo() << "Threads count is out of max value";
        ThreadsCount = sysconf(_SC_STREAM_MAX) - 3; // main, записи в файл и ожидание завершения работы
    }

    ThreadsRead_po = new pthread_t[ThreadsCount];
    ThreadCount_po = new pthread_t;
    ThreadWrite_po = new pthread_t;

    ::ArgTRead_po = new ArgThreadRead[ThreadsCount];
    ::ArgTCount_po = new ArgThreadTasksCount();
    ::ArgTWrite_po = new ArgThreadWrite();

    pthread_attr_init(&Attr_o);

    pthread_mutex_init(&MutexRead_eo, nullptr);
    pthread_cond_init(&CondRead_eo, nullptr);

    //-------------------------------------------------заполнение входных параметров

    ArgTCount_po->_ThreadsCount_i = ThreadsCount;
    ArgTCount_po->_Process_po = _Process;

    for (int i = 0; i < ThreadsCount; ++i) {
        ArgTRead_po[i]._Process_po = _Process;
        ArgTRead_po[i]._IndexThread_i = i;
        ArgTRead_po[i]._IsLastThread_b = false;
        if (i == (ThreadsCount - 1))
            ArgTRead_po[i]._IsLastThread_b = true;
    }

    ArgTWrite_po->_OutputFile_str = OutputFile;
    //-------------------------------------------------создание тредов

    int status = pthread_create(ThreadCount_po, &Attr_o, ThreadTasksCount_v, (void*)ArgTCount_po);
        if (status != 0) {
            //qWarning() << "thread TaskCount has not created, status = " << status;
            exit(ERROR_CREATE_THREAD);
        } //else qInfo() << "thread TaskCount created";

    for (int i = 0; i < ThreadsCount; ++i) {
        int status = pthread_create(&(ThreadsRead_po[i]), &Attr_o, ThreadRead_v, (void*)&ArgTRead_po[i]);
        if (status != 0) {
            //qWarning() << "threads Read has not created, status = " << status;
            exit(ERROR_CREATE_THREAD);
        } //else qInfo() << "threads Read created";
    }

    status = pthread_create(ThreadWrite_po, &Attr_o, ThreadWrite_v, (void*)ArgTWrite_po);
    if (status != 0) {
        //qWarning() << "thread TaskCount has not created, status = " << status;
        exit(ERROR_CREATE_THREAD);
    } //else qInfo() << "thread Write created";
}
