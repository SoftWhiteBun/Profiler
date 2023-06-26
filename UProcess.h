#pragma once

#include <vector>

#include "UTask.h"
#include "UBaseProcess.h"


/**
 * @brief Класс профилируемого процесса */
class Process : public BaseProcess
{
public:
    Process(); // нужен ли вообще?
    /**
     * @brief Process
     * @param Идентификатор процесса */
    explicit Process(int procID);
    /**
     * @brief Метод для пересчета количества потоков процесса */
    void ReCountTasks_v();
    /**
     * @brief Метод для считывания первичной информации о потоках процесса */
    void CreateTasks_v();
    /**
     * @brief Метод для считывания информации обо всех потоках процесса */
    void ReadAllTasks_v();
    /**
     * @brief Метод для получения количества потоков процесса
     * @return Количество потоков процесса */
    int GetTasksCount_i();

    /**
     * @brief Метод, закрепляющий поток профилируемого процесса за потоком приложения
     * @param indexThread Номер потока приложения
     * @param indexTask Идентификатор потока профилируемого процесса */
    void PushElemToMatrix_v(int indexThread, int indexTask);
    /**
     * @brief Метод для очистки матрицы соответствия потоков профилируемого процесса потокам приложения*/
    void ClearMatrix_v();
    /**
     * @brief Метод для чтения потоков профилируемого процесса, закрепленных за потоком приложения
     * @param indexThread Номер потока приложения
     * @param CurrentTime Количество прошедших тиков таймера */
    void ReadTasksForThread_v(int indexThread, unsigned int CurrentTime);
private:
    std::string _TaskDirPath_str; ///< @brief Путь до директории потоков процесса в ОС
    std::vector<Task*> _ProcTasks_vec; ///< @brief Вектор указателей на потоки процесса
    int _ProcTasksCount_i; ///< @brief Количество потоков процесса

    std::vector< std::vector<int> > _ThreadPidMatrix_vec; ///< @brief Матрица соответствия потоков профилируемого процесса считывающим потокам приложения
};

