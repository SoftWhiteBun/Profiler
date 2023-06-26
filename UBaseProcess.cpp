#include "UBaseProcess.h"

#include <cstring>
#include <string>

//#include "SLogger.h"

BaseProcess::BaseProcess()
    : _Name_str("")
    , _PID_i(0)
    , _Processor_i(0)
    , _State_en(DEAD)
    , _StatusPath_s("")
{

}



void BaseProcess::ReadDataFromStatFile_v()
{
    FILE* PStatusFile = fopen(_StatusPath_s.c_str(), "r");

    if (!PStatusFile) {
//        qWarning() << ("Process status file doesn't open");
        exit(ERROR_OPEN_FILE);
    }

    const int StatBufferLength_ci = 512;
    char fileBuffer[ StatBufferLength_ci ];
    char tmpBuffer[32];
    int tmpCounter = 0;
    int spaceCounter = 0;

    fread(fileBuffer, StatBufferLength_ci, 1, PStatusFile);
    for (size_t i = 0; i < strlen( fileBuffer ); ++i) {
      if (fileBuffer[i] == ' ') {
        tmpBuffer[tmpCounter] = '\0';

        switch(spaceCounter) {

        case 0: this->_PID_i = atoi(tmpBuffer); break;

        case 1: this->_Name_str = tmpBuffer; break;

        case 2: {
                 if (strcmp( &tmpBuffer[0], "X" ) == 0)
                     _State_en = DEAD;
            else if (strcmp( &tmpBuffer[0], "I" ) == 0)
                     _State_en = IDLE_KERNEL_THREAD;
            else if (strcmp( &tmpBuffer[0], "R" ) == 0)
                     _State_en = RUNNING;
            else if (strcmp( &tmpBuffer[0], "S" ) == 0)
                     _State_en = SLEEP;
            else if (strcmp( &tmpBuffer[0], "T" ) == 0)
                     _State_en = STOPPED;
            else if (strcmp( &tmpBuffer[0], "t" ) == 0)
                     _State_en = STOPPED_DEBUG;
            else if (strcmp( &tmpBuffer[0], "D" ) == 0)
                     _State_en = UNINTERRUPT_SLEEP;
            else if (strcmp( &tmpBuffer[0], "Z" ) == 0)
                     _State_en = ZOMBIE;
            break;
        }

        case 38:
          this->_Processor_i = atoi(tmpBuffer);
          i = StatBufferLength_ci; // Конец работы
          break;
        }

        tmpBuffer[0] = '\0';
        tmpCounter = 0;
        ++spaceCounter;
        continue;
      }
      tmpBuffer[tmpCounter++] = fileBuffer[i];
    }
    fclose(PStatusFile);
}


//void AProc::GetInfo() {
//    qInfo() << "Name: " << QString::fromStdString(this->Name);
//    qInfo() << "Pid: " << this->PID;
//    //qInfo() << "PPid: " << this->PPID;
//    switch (this->State) {
//    case DEAD: {
//        qInfo() << "State: X";
//        break;
//    }
//    case IDLE_KERNEL_THREAD: {
//        qInfo() << "State: I";
//        break;
//    }
//    case RUNNING: {
//        qInfo() << "State: R";
//        break;
//    }
//    case SLEEP: {
//        qInfo() << "State: S";
//        break;
//    }
//    case STOPPED: {
//        qInfo() << "State: T";
//        break;
//    }
//    case STOPPED_DEBUG: {
//        qInfo() << "State: t";
//        break;
//    }
//    case UNINTERRUPT_SLEEP: {
//        qInfo() << "State: D";
//        break;
//    }
//    case ZOMBIE: {
//        qInfo() << "State: Z";
//        break;
//    }

//    }
//}


//void AProc::WriteInfo() {
//    std::cout << "Name: " << this->Name << std::endl;
//    std::cout << "Pid: " << this->PID << std::endl;
//    switch (this->State) {
//    case DEAD: {
//        std::cout << "State: X" << std::endl;
//        break;
//    }
//    case IDLE_KERNEL_THREAD: {
//        std::cout << "State: I" << std::endl;
//        break;
//    }
//    case RUNNING: {
//        std::cout << "State: R" << std::endl;
//        break;
//    }
//    case SLEEP: {
//        std::cout << "State: S" << std::endl;
//        break;
//    }
//    case STOPPED: {
//        std::cout << "State: T" << std::endl;
//        break;
//    }
//    case STOPPED_DEBUG: {
//        std::cout << "State: t" << std::endl;
//        break;
//    }
//    case UNINTERRUPT_SLEEP: {
//        std::cout << "State: D" << std::endl;
//        break;
//    }
//    case ZOMBIE: {
//        std::cout << "State: Z" << std::endl;
//        break;
//    }

//    }
//}


int BaseProcess::GetPID_i() const
{
    return _PID_i;
}

EnStatus BaseProcess::GetState_en() const
{
    return _State_en;
}

char BaseProcess::GetState_c() const
{
    char ReturnCode_c = 0;
    switch (_State_en) {
    case DEAD: {
        ReturnCode_c = 'X';
    } break;
    case IDLE_KERNEL_THREAD: {
        ReturnCode_c = 'I';
    } break;
    case RUNNING: {
        ReturnCode_c = 'R';
    } break;
    case SLEEP: {
        ReturnCode_c = 'S';
    } break;
    case STOPPED: {
        ReturnCode_c = 'T';
    } break;
    case STOPPED_DEBUG: {
        ReturnCode_c = 't';
    } break;
    case UNINTERRUPT_SLEEP: {
        ReturnCode_c = 'D';
    } break;
    case ZOMBIE: {
        return 'Z';
    } break;
    default: break;
    }
    return ReturnCode_c;
}

int BaseProcess::GetProcessor_i() const
{
    return _Processor_i;
}




























