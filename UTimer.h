#pragma once

//#include "SLogger.h"

//#include <signal.h>
#include <time.h>
//#include <iostream>
//#include <unistd.h>
//#include <sys/time.h>

/**
 * @class Timer
 * @brief Класс таймера, который вызывает пользовательские функции
 *
 * @details
 *
 *
 * @date 04.03.2023
 * @author Баранович С. К. */
class Timer
{
public:
    Timer();
    /**
     * @brief Метод для инициализации и запуска таймера
     * @param delta Период снятия данных о профилируемом процессе и его потоках
     * @param count Период пересчета количества потоков */
    void StartTimer_v(int delta, int count); //, void(*handler)()
    /** @brief */
    void StopTimer_v(); //---------------------------

    unsigned int GetTime_ui();
private:
    int _TimerFD_i; ///< @brief
    struct itimerspec _Value_o; ///< @brief

    /**
     * @brief Метод-обработчик срабатывания таймера. Запускает снятие данных о профилируемом процессе  */
    void DeltaHandler_v();
    /** @brief Метод-обработчик срабатывания таймера. Запускает пересчет количества потоков профилируемого процесса */
    void CountHandler_v();
};


//отсчет времени + сигнал
//void sigusr_handler2(int signo);
//void sigusr_handler();
//void InitTimer_v3 (int delta, void(*handler)()); //int



//void InitTimer (int delta, void(*handler)(int));
//void InitTimer_v2 (int delta, void(*handler)(int));
