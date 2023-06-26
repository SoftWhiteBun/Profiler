#include "UProcessDoubleBuffer.h"

#include <cstring>

#include "CConstants.h"

ProcessDoubleBuffer& ProcessDoubleBuffer::GetInstance_rso()
{
    static ProcessDoubleBuffer instance;
    return instance;
}

void ProcessDoubleBuffer::AddInfo_v(int PID, char state, int processor, unsigned int time)
{
    unsigned char * currentBufferPointer = _PointToBuffer_puc + _Position_ui;
    _Position_ui += 16; // 4 байта на pid + 1 байт на состояние + 4 байта номер CPU + 4 байта время + 1 (резерв)
    // Запись в выходной буфер
    memcpy(currentBufferPointer,      (void*)&PID,         4);
    memcpy(currentBufferPointer + 4,  (void*)&state,       1);
    memcpy(currentBufferPointer + 5,  (void*)&processor,   4);
    memcpy(currentBufferPointer + 9,  (char*)&time,        4);
    if (_Position_ui + 17 > _BufferSize_sci) { // Если заполнился, то переключим его
      _SavedPosition_ui.store(_Position_ui);
      _Position_ui = 0;
      _PointToBuffer_puc = (_PointToBuffer_puc == _DoubleBuffer1_puc) ? _DoubleBuffer2_puc : _DoubleBuffer1_puc;

      pthread_mutex_lock(&MutexWrite_eo);
      pthread_cond_broadcast(&CondWrite_eo);
      pthread_mutex_unlock(&MutexWrite_eo);
    }
}

unsigned char* ProcessDoubleBuffer::GetBufferToWrite_puc()
{
    if (_PointToBuffer_puc == _DoubleBuffer2_puc)
        return _DoubleBuffer1_puc;
    return _DoubleBuffer2_puc;
}

void ProcessDoubleBuffer::ResetSavedPosition_v()
{
    _SavedPosition_ui.store(0);
}

unsigned int ProcessDoubleBuffer::GetSavedPosition_ui()
{
    return _SavedPosition_ui.load();
}

unsigned int ProcessDoubleBuffer::GetPosition_ui()
{
    return _Position_ui;
}

unsigned char* ProcessDoubleBuffer::GetCurrentBuffer_puc()
{
    return _PointToBuffer_puc;
}

ProcessDoubleBuffer::ProcessDoubleBuffer()
    : _Position_ui(0)
    , _SavedPosition_ui(0)
{
    _DoubleBuffer1_puc = new unsigned char[_BufferSize_sci];
    _DoubleBuffer2_puc = new unsigned char[_BufferSize_sci];
    _PointToBuffer_puc = _DoubleBuffer1_puc;
}

ProcessDoubleBuffer::ProcessDoubleBuffer(const ProcessDoubleBuffer & /*origin*/)
{

}

ProcessDoubleBuffer::~ProcessDoubleBuffer()
{
    delete _DoubleBuffer1_puc;
    delete _DoubleBuffer2_puc;
}
