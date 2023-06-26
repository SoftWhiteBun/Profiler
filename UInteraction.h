#pragma once

#include <string>

/**
 * @brief Класс аргументов, передаваемых пользователем приложению */
class Interaction
{
public:
    explicit Interaction(int ArgC_i, char** ArgV_pc);

    /**
     * @brief Метод для получения значения периода снятия данных о процессе и его потоках в микросекундах
     * @return Значение периода снятия данных о процессе и его потоках в микросекундах */
    int GetDelta_i();
    /**
     * @brief Метод для получения значения периода пересчета потоков профилируемого процесса в микросекундах
     * @return Значение периода пересчета потоков профилируемого процесса в микросекундах */
    int GetCount_i();
    /**
     * @brief Метод для получения идентификатора профилируемого процесса
     * @return Идентификатор профилируемого процесса */
    int GetPID_i();
    /**
     * @brief Метод для получения количества потоков чтения информации о профилируемом процессе и его потоках
     * @return Количество потоков чтения информации о профилируемом процессе и его потоках */
    int GetThreadsCount_i();
    /**
     * @brief Метод для получения названия выходного файла с собранными данными о профилируемом процессе и его потоках
     * @return Название выходного файла с собранными данными о профилируемом процессе и его потоках */
    std::string GetOutputFile_str();
    /**
     * @brief Метод для получения названия файла с логами приложения
     * @return Название файла с логами приложения */
    std::string GetLogFile_str();

private:
    int _Argc_i;
    char** _Argv_pc;
    int _Delta_i;
    int _Count_i;
    int _PID_i;
    int _ThreadsCount_i;
    std::string _OutputFile_str;
    std::string _LogFile_str;

    /**
     * @brief Метод для вывода справки об использовании приложения */
    void Help_v();
    /**
     * @brief Метод для вывода версии приложения */
    void Version_v();
    /**
     * @brief Метод для проверки количества параметров
     * @param _Argc_i   Количество введенных параметров
     * @param i         Номер текущего параметра */
    void CheckArgc_v(int _Argc_i, int i);
    /**
     * @brief Метод для инициализации параметров из аргументов командной строки */
    void InitUserArgs_v();
};