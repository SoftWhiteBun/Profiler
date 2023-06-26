#pragma once

#include <string>

//#include "SLogger.h"
#include "UBaseProcess.h"

/**
 * @class Task
 * @brief Класс потока профилируемого процесса */
class Task : public BaseProcess
{
public:
    Task();
    /**
     * @brief Task
     * @param taskID Идентификатор потока
     * @param procID Идентификатор порождающего процесса */
    explicit Task(std::string taskID, int procID);
    virtual ~Task() = default;
};


