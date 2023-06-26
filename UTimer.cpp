#include "UTimer.h"

#include <iostream>
#include <sys/timerfd.h>
#include <unistd.h>

#include "CConstants.h"
//#include "FThreads.h"

#if defined(__sparc__)
/// @todo Определения для МЦСТ
#endif // __sparc__


Timer::Timer()
{
    _TimerFD_i = timerfd_create(CLOCK_REALTIME, 0);
}

void Timer::StartTimer_v(int delta, int count)
{
    _Value_o.it_value.tv_sec = 0;
    _Value_o.it_value.tv_nsec = delta * 1000;
    _Value_o.it_interval.tv_sec = 0;
    _Value_o.it_interval.tv_nsec = delta * 1000;

    timerfd_settime(_TimerFD_i, 0, &_Value_o, 0);

    char buf[8];
    int timerCounter = 1; // счетчик для пересчета количества потоков
    while (!IsExit_eb) { // !isExit
        if ((timerCounter % count == 0) || (timerCounter == 1))
            CountHandler_v();
        read(_TimerFD_i, buf, sizeof(buf));
        TimerTicks_eui += 1;
        DeltaHandler_v();
        timerCounter++;
    }
}

void Timer::DeltaHandler_v()
{
    pthread_mutex_lock(&MutexRead_eo);
    fprintf(stdout, "Раз в секунду ---------------\n");
    pthread_cond_broadcast(&CondRead_eo);
    pthread_mutex_unlock(&MutexRead_eo);
}

void Timer::CountHandler_v()
{
    pthread_mutex_lock(&MutexCountWait_eo);
    fprintf(stdout, "Пересчет ---------------------------------\n");
    pthread_cond_signal(&CondCount_eo);
    pthread_mutex_unlock(&MutexCountWait_eo);
}


unsigned int Timer::GetTime_ui()
{
    return 0;
}
