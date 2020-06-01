#include "pch.h"
#include "Debug.h"
#include <iostream>
#include <time.h>
#include "SRHelper.h"

bool SpaRcle::Helper::Debug::ColorThermeIsEnabled = false;
SpaRcle::Helper::Debug::Debug(std::string path, bool init_color_therme) {
    if(init_color_therme)
        InitColorTherme();
    setlocale(LC_ALL, "rus");
    srand(static_cast<unsigned int>(time(0)));

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    show_use_memory = false;
    isConsole = true;
    path_log = path;
    prefix = "";
    //this->log_file = std::ofstream(path + "\\log.txt");
    this->log_file.open(path + "\\log.txt");
    std::string msg = "Debugger is run!";
    Print(msg, Type::_Debug);
}

SpaRcle::Helper::Debug::~Debug() {
    std::string msg = "Debugger has been closed!";
    Print(msg, Type::_Debug);
    this->log_file.close();
}

void SpaRcle::Helper::Debug::Print(std::string& msg, Type type) {
   ret:
    if(!use) {
        use = true;

        ConsoleColor color = ConsoleColor::Black;

        if (log_file.is_open()) {
            switch (type) {
            case SpaRcle::Helper::Debug::Type::_Log:        { prefix = "[Log] ";      color = ConsoleColor::Cyan;       } break;
            case SpaRcle::Helper::Debug::Type::_Info:       { prefix = "[Info] ";     color = ConsoleColor::Magenta;    } break;
            case SpaRcle::Helper::Debug::Type::_System:     { prefix = "[System] ";   color = ConsoleColor::Blue;       } break;
            case SpaRcle::Helper::Debug::Type::_Warning:    { prefix = "[Warn] ";     color = ConsoleColor::Brown;      } break;
            case SpaRcle::Helper::Debug::Type::_Error:      { prefix = "[Error] ";    color = ConsoleColor::Red;        } break;
            case SpaRcle::Helper::Debug::Type::_Fatal:      { prefix = "[Fatal] ";    color = ConsoleColor::Red;        } break;
            case SpaRcle::Helper::Debug::Type::_Debug:      { prefix = "[Debug] ";    color = ConsoleColor::Brown;      } break;
            case SpaRcle::Helper::Debug::Type::_Network:    { prefix = "[Network] ";  color = ConsoleColor::LightBlue;  } break;
            case SpaRcle::Helper::Debug::Type::_Graph:      { prefix = "[Graph] ";    color = ConsoleColor::Green;      } break;
            default:
                Debug::InternalError("Debug : unknown type!");
                break;
            }

            if(show_use_memory)
                std::cout << "<" << ((float)Utils::GetCurrentMemoryLoad()) / 1024.f << " KB> ";
            SetConsoleTextAttribute(hConsole, (WORD)((ConsoleColor::LightGray << 4) | color));
            std::cout << prefix;
            SetConsoleTextAttribute(hConsole, (WORD)((ConsoleColor::LightGray << 4) | ConsoleColor::Black));

            log_file << msg + "\n";
            log_file.flush();
            std::cout << msg + "\n";
        } else
            Debug::InternalError("Log file is not open!\n\tMsg : "+msg);
        use = false;
    } else goto ret;
}
