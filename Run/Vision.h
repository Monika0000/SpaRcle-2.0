#pragma once
#include <Core.h>
#include <vector>
#include <string>
#include <thread>
#include <SRHelper.h>
#include "Neuron.h"

using namespace SpaRcle;
using namespace Network;
using namespace Helper;

class Vision : public Core {
	Vision(std::string core_name, TCP* tcp, Debug* debug, Settings* settings, FileManager* file_manager)
		: Core(core_name, tcp, debug, settings, file_manager) {

	};
};

