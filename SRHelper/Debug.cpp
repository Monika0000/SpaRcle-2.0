#include "pch.h"
#include "Debug.h"

SpaRcle::Helper::Debug::Debug(std::string path) {
    isConsole = true;
    path_log = path;
    prefix = "";
    this->log_file = std::ofstream(path + "\\log.txt");
    Log("Debugger is run!");
}

SpaRcle::Helper::Debug::~Debug() {
    this->log_file.close();
}

void SpaRcle::Helper::Debug::Print(std::string& msg, Type type) {
	switch (type) {
        case SpaRcle::Helper::Debug::Type::_Log:     prefix = "[Log] "; break;
        case SpaRcle::Helper::Debug::Type::_Info:    prefix = "[Info] "; break;
        case SpaRcle::Helper::Debug::Type::_System:  prefix = "[System] "; break;
        case SpaRcle::Helper::Debug::Type::_Warning: prefix = "[Warn] "; break;
        case SpaRcle::Helper::Debug::Type::_Error:   prefix = "[Error] "; break;
        case SpaRcle::Helper::Debug::Type::_Fatal:   prefix = "[Fatal] "; break;
    default:
        break;
	}

    log_file << prefix + msg + "\n";
    std::cout << prefix + msg + "\n";
}
