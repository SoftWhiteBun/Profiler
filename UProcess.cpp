#include <vector>
#include <string>
#include <cstring>
#include <dirent.h>

#include "UProcess.h"
//#include "SLogger.h"
#include "UProcessDoubleBuffer.h"

Process::Process() : BaseProcess()
{
    _ProcTasks_vec.clear();
}

Process::Process(int procID)
{
    _PID_i = procID;
    _State_en = DEAD;
    _ProcTasksCount_i = 0;

    std::string PPath = "/proc/" + std::to_string(_PID_i);
    _StatusPath_s = PPath + "/stat";
    _TaskDirPath_str = PPath + "/task";

    BaseProcess::ReadDataFromStatFile_v();
    CreateTasks_v();

    _ThreadPidMatrix_vec.clear();
}

void Process::ReadAllTasks_v() // Чтение потоков ВСЕХ
{
    int TasksCount = _ProcTasks_vec.size();
    for (int i = 0; i < TasksCount; i++) {
        _ProcTasks_vec[i]->ReadDataFromStatFile_v();
    }
}

int Process::GetTasksCount_i() {
    return _ProcTasksCount_i;
}

void Process::ReCountTasks_v()  // Пересчет потоков ДОБАВИТЬ ПРОВЕРКУ НА СОВПАДЕНИЕ PID
{
    //ProcTasks.clear();
    DIR *TaskDir;
    struct dirent *entry;
    int TasksCount = 0;

    TaskDir = opendir(_TaskDirPath_str.c_str());
    if (!TaskDir) {
//        qWarning() << "can't open task dir";
        exit(ERROR_OPEN_TASKDIR);
    }
    while ((entry = readdir(TaskDir)) != nullptr) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            TasksCount += 1;
        }
    }
    _ProcTasks_vec.resize(TasksCount);
    _ProcTasksCount_i = TasksCount;
    closedir(TaskDir);
}

void Process::CreateTasks_v()  // Создание потоков: пересчет + чтение
{
    _ProcTasks_vec.clear();
    DIR *TaskDir;
    struct dirent *entry;
    int TasksCount = 0;

    TaskDir = opendir(_TaskDirPath_str.c_str());
    if (!TaskDir) {
//        qWarning() << "can't open task dir";
        exit(ERROR_OPEN_TASKDIR);
    }
    while ((entry = readdir(TaskDir)) != nullptr) {
        TasksCount += 1;
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            Task* T = new Task(entry->d_name, _PID_i);
            _ProcTasks_vec.push_back(T);
        }
    }
    _ProcTasksCount_i = _ProcTasks_vec.size();
    closedir(TaskDir);
}


void Process::ClearMatrix_v()
{
    _ThreadPidMatrix_vec.clear();
}

void Process::PushElemToMatrix_v(int indexThread, int indexTask)
{
    while (static_cast<int>( _ThreadPidMatrix_vec.size() ) < (indexThread + 1)) {
        std::vector<int> tmpVector;
        tmpVector.clear();
        _ThreadPidMatrix_vec.push_back(tmpVector);
    }
    _ThreadPidMatrix_vec[ indexThread ].push_back(  indexTask  );
}

void Process::ReadTasksForThread_v(int indexThread, unsigned int CurrentTime)
{
    if (static_cast<int>( _ThreadPidMatrix_vec.size() ) < (indexThread + 1))
        Process::ReadAllTasks_v();
    else {
        for (int i: _ThreadPidMatrix_vec[ indexThread ]) {
            _ProcTasks_vec[i]->ReadDataFromStatFile_v();
            ProcessDoubleBuffer& _DoubleBuffer = ProcessDoubleBuffer::GetInstance_rso();
            _DoubleBuffer.AddInfo_v(_ProcTasks_vec[i]->GetPID_i(), _ProcTasks_vec[i]->GetState_c(), _ProcTasks_vec[i]->GetProcessor_i(), CurrentTime);
        }
    }
}



























