#include "pch.h"
#include "Compiler.h"
#include "SREngine.h"

namespace SpaRcle {
	using namespace Helper;
	namespace Engine {
		namespace Scripting {
			Compiler::Compiler(SREngine* engine, Debug* debug) {
				this->engine = engine;
				this->debug  = debug;
			}
			Compiler::~Compiler() {

			}
			void Compiler::AddScript(Script* script) {
				this->scripts.push_back(script);
			}
			bool Compiler::Compile() {
				debug->Script("Compiling " + std::to_string(scripts.size()) + " scripts...");

				for (auto s : scripts)
					if (!s->Compile(engine, debug)) { 
						//debug->Error("Compiler : Failed compiling scripts! Script : " + s->GetName());
						//return false; 
					}

				return true;
			}
			bool Compiler::Recompile()
			{
				return false;
			}
		}
	}
}