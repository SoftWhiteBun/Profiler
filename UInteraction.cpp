#include "UInteraction.h"

#include <iostream>

Interaction::Interaction(int ArgC_i, char**ArgV_pc)
    : _Delta_i(0)
    , _Count_i(0)
    , _PID_i(0)
    , _ThreadsCount_i(0)
    , _OutputFile_str("")
    , _LogFile_str("")
{
    _Argc_i = ArgC_i;
    _Argv_pc = ArgV_pc;

    InitUserArgs_v();
}

int Interaction::GetDelta_i()
{
    return _Delta_i;
}

int Interaction::GetCount_i()
{
    return _Count_i;
}

int Interaction::GetPID_i()
{
    return _PID_i;
}

int Interaction::GetThreadsCount_i()
{
    return _ThreadsCount_i;
}

std::string Interaction::GetOutputFile_str()
{
    return _OutputFile_str;
}

std::string Interaction::GetLogFile_str()
{
    return _LogFile_str;
}

void Interaction::Help_v()
{
    std::cout << "Справка:\n"
                 "Номер процесса:                                             --pid(-p) X\n"
                 "Период снятия показаний в мкс:                              --delta(-d) X\n"
                 "Имя выходного файла:                                        --file(-f) X\n"
                 "Количество потоков приложения:                              --threads(-t) X\n"
                 "Период проверки количества потоков процесса в мкс:          --count(-c) X\n"
                 "Версия:                                                     --version(-v)\n"
                 "Помощь:                                                     --help(-h)"
              << std::endl;

    exit(0);
}

void Interaction::Version_v()
{
    std::cout << "Версия 1.0" << std::endl;
}


void Interaction::CheckArgc_v(int Argc_i, int i)
{
    if (Argc_i <= (i+1)) {
        Help_v();
        exit(-1);
    }
}

void Interaction::InitUserArgs_v()
{
    for (int i = 1; i < _Argc_i; ++i) {
        std::string param( _Argv_pc[i] );

        if (param == "-p" || param == "--pid") {
            CheckArgc_v(_Argc_i, i);
            _PID_i = atoi( _Argv_pc[i+1] );
        }

        if (param == "-d" || param == "--delta") {
            CheckArgc_v(_Argc_i, i);
            _Delta_i = atoi( _Argv_pc[i+1] );
        }

        if (param == "-f" || param == "--file") {
            CheckArgc_v(_Argc_i, i);
            _OutputFile_str = _Argv_pc[i+1];
        }

        if (param == "-l" || param == "--logfile") { // -l лог по умолчанию --logfile файл юзера ??
            CheckArgc_v(_Argc_i, i);
            _LogFile_str = _Argv_pc[i+1];
        }

        if (param == "-t" || param == "--threads") {
            CheckArgc_v(_Argc_i, i);
            _ThreadsCount_i = atoi( _Argv_pc[i+1] );
        }

        if (param == "-c" || param == "--count") {
            CheckArgc_v(_Argc_i, i);
            _Count_i = atoi(_Argv_pc[i+1]);
        }

        if (param == "-h" || param == "--help")
            Help_v();

        if (param == "-v" || param == "--version")
            Version_v();
    }

    if (_PID_i == 0 || _Delta_i == 0)
        Help_v();

    if (_Count_i == 0)
        _Count_i = 100;

    if (_OutputFile_str == "")
        _OutputFile_str = "ProfilingData";
}

