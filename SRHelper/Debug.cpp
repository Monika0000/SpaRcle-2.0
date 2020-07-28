#include "pch.h"
#include "Debug.h"
#include <iostream>
#include <time.h>
#include "SRHelper.h"
#include <locale.h>
#include <stdio.h>
#include <Windows.h>

bool SpaRcle::Helper::Debug::ColorThermeIsEnabled = false;
SpaRcle::Helper::Debug::Debug(std::string path, bool init_color_therme) {
    if (init_color_therme) {
        InitColorTherme();
    }
    setlocale(LC_ALL, "rus");
    setlocale(LC_NUMERIC, "C");
    srand(static_cast<unsigned int>(time(0)));

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    show_use_memory = false;
    isConsole = true;
    path_log = path;
    prefix = "";
    //this->log_file = std::ofstream(path + "\\log.txt");
    this->log_file.open(path + "\\log.txt");
    std::string msg = "Debugger is run!";
    Print(msg, Type::_Debug, 0);
}

SpaRcle::Helper::Debug::~Debug() {
    std::string msg = "Debugger has been closed!";
    Print(msg, Type::_Debug, 0);
    this->log_file.close();
}

void SpaRcle::Helper::Debug::Print(std::string& msg, Type type, int deep_level) {
   ret:
    if(!use) {
        use = true;

        ConsoleColor color = ConsoleColor::Black;

        if (log_file.is_open()) {
            for (int i = 0; i < deep_level; i++)
                std::cout << "\t";

            switch (type) {
                case SpaRcle::Helper::Debug::Type::_Log:        { prefix = "[Log] ";           color = ConsoleColor::Cyan;         } break;
                case SpaRcle::Helper::Debug::Type::_Info:       { prefix = "[Info] ";          color = ConsoleColor::Magenta;      } break;
                case SpaRcle::Helper::Debug::Type::_System:     { prefix = "[System] ";        color = ConsoleColor::Blue;         } break;
                case SpaRcle::Helper::Debug::Type::_Warning:    { prefix = "[Warn] ";          color = ConsoleColor::Brown;        } break;
                case SpaRcle::Helper::Debug::Type::_Error:      { prefix = "[Error] ";         color = ConsoleColor::Red;          } break;
                case SpaRcle::Helper::Debug::Type::_Fatal:      { prefix = "[Fatal] ";         color = ConsoleColor::Red;          } break;
                case SpaRcle::Helper::Debug::Type::_Debug:      { prefix = "[Debug] ";         color = ConsoleColor::Brown;        } break;
                case SpaRcle::Helper::Debug::Type::_Network:    { prefix = "[Network] ";       color = ConsoleColor::LightBlue;    } break;
                case SpaRcle::Helper::Debug::Type::_Graph:      { prefix = "[Graph] ";         color = ConsoleColor::Green;        } break;
                case SpaRcle::Helper::Debug::Type::_Shader:     { prefix = "[Shader] ";        color = ConsoleColor::LightCyan;    } break;
                case SpaRcle::Helper::Debug::Type::_Script:     { prefix = "[Script] ";        color = ConsoleColor::LightMagenta; } break;
                case SpaRcle::Helper::Debug::Type::_ScriptError:{ prefix = "[SError] ";        color = ConsoleColor::Red;          } break;
            default:
                Debug::InternalError("Debug : unknown type!");
                break;
            }

            if (show_use_memory) {
                float mem = ((float)Utils::GetCurrentMemoryLoad()) / 1024.f;
                std::cout << "<" << mem << " KB> ";
                log_file << "<" << mem << " KB> ";
            }
            SetConsoleTextAttribute(hConsole, (WORD)(((int)ConsoleColor::LightGray << 4) | (int)color));
            std::cout << prefix;
            SetConsoleTextAttribute(hConsole, (WORD)(((int)ConsoleColor::LightGray << 4) | (int)ConsoleColor::Black));

            //Utils::GetContext().
         

            log_file << prefix << msg + "\n";
            log_file.flush();
            std::cout << msg + "\n";
        } else
            Debug::InternalError("Log file is not open!\n\tMsg : "+msg);
        use = false;
    } else goto ret;
}
