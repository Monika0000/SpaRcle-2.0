#include "pch.h"
#include "Core.h"
#include <TCP.h>

namespace SpaRcle {
	using namespace Network;

	bool Core::Close() {
		isRun = false;

		debug->Info("Close core \"" + core_name + "\"...");

		if (task.joinable()) task.join();

		if(tcp) tcp->Close();

		return Completed();
	}
}