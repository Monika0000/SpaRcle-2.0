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
	public:
		ISystem(Debug*debug, Settings*settings) : isRun(false), debug(debug), settings(settings) {

		}
	public:
		virtual bool Run() = 0;
		virtual bool Close() = 0;
	};
}