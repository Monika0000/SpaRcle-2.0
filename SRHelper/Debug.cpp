#include "pch.h"
#include "Debug.h"
#include <iostream>
#include <time.h>

SpaRcle::Helper::Debug::Debug(std::string path) {
    system("color 70");
    setlocale(LC_ALL, "rus");
    srand(static_cast<unsigned int>(time(0)));

    isConsole = true;
    path_log = path;
    prefix = "";
   // this->log_file = std::ofstream(path + "\\log.txt");
    this->log_file.open(path + "\\log.txt");
    std::string msg = "Debugger is run!";
    Print(msg, Type::_Debug);
}

SpaRcle::Helper::Debug::~Debug() {
    this->log_file.close();
}

void SpaRcle::Helper::Debug::Print(std::string& msg, Type type) {
    if (log_file.is_open()) {
        switch (type) {
        case SpaRcle::Helper::Debug::Type::_Log:     prefix = "[Log] "; break;
        case SpaRcle::Helper::Debug::Type::_Info:    prefix = "[Info] "; break;
        case SpaRcle::Helper::Debug::Type::_System:  prefix = "[System] "; break;
        case SpaRcle::Helper::Debug::Type::_Warning: prefix = "[Warn] "; break;
        case SpaRcle::Helper::Debug::Type::_Error:   prefix = "[Error] "; break;
        case SpaRcle::Helper::Debug::Type::_Fatal:   prefix = "[Fatal] "; break;
        case SpaRcle::Helper::Debug::Type::_Debug:   prefix = "[Debug] "; break;
        case SpaRcle::Helper::Debug::Type::_Network: prefix = "[Network] "; break;
        default:
            Debug::InternalError("Debug : unknown type!");
            break;
        }
        log_file << prefix + msg + "\n";
        log_file.flush();
        std::cout << prefix + msg + "\n";
    } else
        Debug::InternalError("Log file is not open!");
}
