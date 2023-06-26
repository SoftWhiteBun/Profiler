#include "CConstants.h"


bool IsExit_eb = false;

pthread_cond_t CondRead_eo;
pthread_mutex_t MutexRead_eo;

pthread_cond_t CondCount_eo;
pthread_mutex_t MutexCountWait_eo;
pthread_mutex_t MutexCountResize_eo;

pthread_cond_t CondWrite_eo;
pthread_mutex_t MutexWrite_eo;

std::atomic<unsigned int> TimerTicks_eui(0);
