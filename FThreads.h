#pragma once

#include "UProcess.h"

//extern volatile bool isExit;

void CreateThreads_v(int ThreadsCount, Process* Proc, std::string OutputFile);
void SigintHandler_v (int signo);

