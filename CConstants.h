#pragma once

#include <pthread.h>
#include <atomic>

/**
 * @brief Перечисление возможных ошибок при работе программы */
enum EnError
{
    SUCCESS = 0,
    ERROR_OPEN_FILE,
    ERROR_OPEN_TASKDIR,
    ERROR_CREATE_THREAD,
    ERROR_JOIN_THREAD
};

/**
 * @brief Перечисление состояний процесса и потоков */
enum EnStatus
{
    DEAD = 0,                   ///< @brief X
    IDLE_KERNEL_THREAD,         ///< @brief I
    RUNNING,                    ///< @brief R
    SLEEP,                      ///< @brief S
    STOPPED,                    ///< @brief T
    STOPPED_DEBUG,              ///< @brief t
    UNINTERRUPT_SLEEP,          ///< @brief D
    ZOMBIE,                     ///< @brief Z
    MUTEX_LOCK                  ///< @brief M, only Elbrus
};

extern bool IsExit_eb; ///< @brief Условие окончания программы

extern pthread_cond_t CondRead_eo; ///< @brief Условная переменная ожидания исполнения потока чтения информации о профилируемом процессе и его потоках
extern pthread_mutex_t MutexRead_eo; ///< @brief Мьютекс потока чтения

extern pthread_cond_t CondCount_eo; ///< @brief Условная переменная ожидания исполнения потока пересчета потоков профилируемого процесса
extern pthread_mutex_t MutexCountWait_eo; ///< @brief Мьютекс ожидания исполнения потока пересчета потоков профилируемого процесса
extern pthread_mutex_t MutexCountResize_eo; ///< @brief Мьютекс для изменения количества потоков профилируемого процесса

extern pthread_cond_t CondWrite_eo; ///< @brief Условная переменная ожидания записи заполненного буфера в файл
extern pthread_mutex_t MutexWrite_eo; ///< @brief Мьютекс ожидания записи заполненного буфера в файл

extern std::atomic<unsigned int> TimerTicks_eui;
