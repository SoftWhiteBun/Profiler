#pragma once

#include <string>

#include "CConstants.h"

// ------------- модификаторы состояния процесса
//               <    high-priority (not nice to other users)
//               N    low-priority (nice to other users)
//               L    has pages locked into memory (for real-time and
//                    custom IO)
//               s    is a session leader
//               l    is multi-threaded (using CLONE_THREAD, like NPTL
//                    pthreads do)
//               +    is in the foreground process group

class BaseProcess
{
public:
    BaseProcess(); // нужен ли вообще?
    /**
     * @brief Метод чтения информации об объекте из файла Stat в ОС */
    void ReadDataFromStatFile_v();
    /**
     * @brief Метод для получения идентификатора объекта (процесса или потока)
     * @return Идентификатор объекта (процесса или потока) */
    int GetPID_i() const;
    /**
     * @brief Метод для получения состояния объекта (процесса или потока) в формате перечисления
     * @return Состояние объекта (процесса или потока) */
    EnStatus GetState_en() const;
    /**
     * @brief Метод для получения состояния объекта (процесса или потока) в строковом формате
     * @return Состояние объекта (процесса или потока) */
    char GetState_c() const;
    /**
     * @brief Метод для получения номера процессора, который исполнял процесс или поток последним
     * @return Номер процессора, исполнявшего процесс или поток последним*/
    int GetProcessor_i() const;

protected:
    std::string _Name_str; ///< @brief Имя процесса или потока
    int _PID_i; ///< @brief Идентификатор процесса или потока
    int _Processor_i; ///< @brief Номер процессора, который исполнял процесс или поток последним
    EnStatus _State_en; ///< @brief Состояние процесса или потока
    std::string _StatusPath_s; ///< @brief Путь до файла Stat в ОС
};

