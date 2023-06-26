#include "UTask.h"

#include <string>

#include "UProcess.h"

//#include <cstdio>


Task::Task()
    : BaseProcess()
{

}

Task::Task(std::string taskID, int procID)
{
    _PID_i = std::atoi(taskID.c_str());
    _State_en = DEAD;
    _StatusPath_s = "/proc/" + std::to_string(procID) + "/task/" + taskID + "/stat";

    BaseProcess::ReadDataFromStatFile_v();
}





























