#pragma once
#include <SRHelper.h>
#include "Settings.h"
using namespace SpaRcle::Helper;

namespace SpaRcle {
	class ISystem {
	protected:
		bool isRun;
		Debug* debug;
		Settings* settings;
		FileManager* fileManager;
	public:
		ISystem(Debug*debug, Settings*settings, FileManager* fileManager) : isRun(false), debug(debug), settings(settings), fileManager(fileManager) {

		}
	public:
		virtual bool Run() = 0;
		virtual bool Close() = 0;
	};
}