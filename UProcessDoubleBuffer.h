#pragma once

//#include <stdlib.h>
#include <atomic>

/**
 * @class ProcessDoubleBuffer
 * @brief Класс синглтон, реализующий двойную буферизацию для работы с данными о профилируемом процессе */
class ProcessDoubleBuffer
{
public:
    static ProcessDoubleBuffer& GetInstance_rso();

    /**
     * @brief Метод для добавления данных в буфер
     * @param PID Идентификатор процесса или потока
     * @param state Состояние процесса или потока
     * @param processor Номер процессора, который исполнял процесс или поток последним
     * @param time Количество прошедших тиков таймера */
    void AddInfo_v(int PID, char state, int processor, unsigned int time); // Добавить запись времени?
    /**
     * @brief Метод для получения указателя на заполненный буфер, готовый для записи в файл
     * @return Указатель на буфер */
    unsigned char* GetBufferToWrite_puc();
    /**
     * @brief Метод, обнуляющий указатель на сохраненную позицию в буфере */
    void ResetSavedPosition_v();
    /**
     * @brief Метод для получения позиции последнего символа в заполненном буфере. Также служит для получения размера заполненного буфера в байтах
     * @return Позиция последнего символа */
    unsigned int GetSavedPosition_ui();
    /**
     * @brief Метод для получения позиции последнего записанного в буфер символа
     * @return Позиция последнего записанного символа */
    unsigned int GetPosition_ui();
    /**
     * @brief Метод для получения указателя на текущий открытый для записи буфер
     * @return Указатель на буфер */
    unsigned char* GetCurrentBuffer_puc();

private:
    ProcessDoubleBuffer();
    ProcessDoubleBuffer( const ProcessDoubleBuffer&);
    ProcessDoubleBuffer& operator=( ProcessDoubleBuffer& );
    virtual ~ProcessDoubleBuffer();

    static const int _BufferSize_sci = 1600;
    unsigned char* _DoubleBuffer1_puc;
    unsigned char* _DoubleBuffer2_puc;
    unsigned char* _PointToBuffer_puc;
    std::atomic<unsigned int> _Position_ui;
    std::atomic<unsigned int> _SavedPosition_ui; // Текущая позиция записи
};


