#pragma once
#include "Script.h"
#include <SRHelper.h>

namespace SpaRcle {
	using namespace Helper;
	namespace Engine {
		class SREngine;
		namespace Scripting {
			class Compiler {
				friend class SREngine;
			public:
				Compiler(SREngine* engine, Debug* debug);
				~Compiler();
			private:
				std::vector<Script*> scripts = std::vector<Script*>();
				SREngine* engine			 = nullptr;
				Debug* debug				 = nullptr;
				bool isCompile				 = false;
			public:
				void AddScript(Script* script);
				bool Compile();
				bool Recompile();
			};
		}
	}
}

