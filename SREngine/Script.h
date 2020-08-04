#pragma once
#include <iostream>
#include <string>
#include <vector>

#include <Debug.h>

#pragma comment(lib,"lua.lib")
extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
//	#include <lua.hpp>
//	#include <luaconf.h>
}
#include <LuaBridge/LuaBridge.h>

namespace SpaRcle {
	using namespace Helper;
	namespace Engine {
		class SREngine;
		namespace Scripting {
			class Compiler;

			class ScriptFunctions {

			};

			class Script {
				friend class Compiler;
			private:
				std::string lua_script  = "Unnamed";
				bool isCompile		    = false;
				bool hasErrors		    = false;
				lua_State* L		    = nullptr;
				Debug* debug		    = nullptr;
				int r				    = -1;
			private:
				bool RegisterStandartFunctions();
				bool RegisterStandartVariables();
				bool Compile(SREngine* engine, Debug* debug); 
			public:
				Script(std::string lua_script);
				~Script();
			public:
				static SREngine* engine;
			public:
				const std::string GetName() const noexcept { return lua_script; };
				const bool HasErrors() const noexcept { return hasErrors; };
				const bool IsCompile() const noexcept { return isCompile; };
			public:
				bool Init();
				bool Start();
				bool Update(float time);
				bool Close();
			};
		}
	}
}

