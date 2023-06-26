#pragma once

#include "UProcess.h"

/**
 * @brief Класс аргументов для потока чтения информации о профилируемом процессе и его потоках  из ОС*/
class ArgThreadRead
{
public:
    Process* _Process_po; ///< @brief Указатель на объект профилируемого процесса
    int _IndexThread_i; ///< @brief Номер исполняемого потока приложения
    bool _IsLastThread_b; ///< @brief Является ли номер потока последним. Необходимо для чтения информации о самом процессе
};

/**
 * @brief Класс аргументов для потока пересчета потоков профилируемого процесса */
class ArgThreadTasksCount
{
public:
    int _ThreadsCount_i; ///< @brief Количество потоков чтения информации о профилируемом процессе и его потоках из ОС
    Process* _Process_po; ///< @brief Указатель на объект профилируемого процесса
};

/**
 * @brief Класс аргументов для потока записи заполненного буфера данных в файл */
class ArgThreadWrite
{
public:
    std::string _OutputFile_str; ///< @brief Название выходного файла с информацией о процессе и его потоках
};

pthread_t* ThreadsRead_po; ///< @brief Глобальный указатель на поток чтения информации о профилируемом процессе из ОС
pthread_t* ThreadCount_po; ///< @brief Глобальный указатель на поток пересчета количества потоков профилируемого процесса
pthread_t* ThreadWrite_po; ///< @brief Глобальный указатель на поток записи заполненного буфера данных в выходной файл
pthread_attr_t Attr_o;

ArgThreadRead* ArgTRead_po;
ArgThreadTasksCount* ArgTCount_po;
ArgThreadWrite* ArgTWrite_po;

