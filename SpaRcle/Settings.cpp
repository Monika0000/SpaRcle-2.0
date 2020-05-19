#include "pch.h"
#include <SRHelper.h>
#include "Settings.h"

SpaRcle::Settings::Settings(std::string path) {
	if (!path.empty()) this->path_to_exe = path; else path_to_exe = Helper::Utils::GetPathToExe();

	this->memory_path = path + "\\Memory";
}

SpaRcle::Settings::~Settings() {

}
