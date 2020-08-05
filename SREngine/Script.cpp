#include "pch.h"	
#include "Script.h"
#include <SRHelper.h>
#include "SREngine.h"

namespace SpaRcle {
	using namespace Helper;
	namespace Engine {
		namespace Scripting {
			using namespace luabridge;

			SREngine* Script::engine = nullptr;

			typedef Material* pMaterial;
			//void foo(std::string str) {
			//	std::cout << "foo = " << str << std::endl;
			//}

			//void Lambda(std::function<void()> fun) { fun(); }

			bool Script::RegisterStandartFunctions() {
				/*
				//auto a = &debug->Log;
				//void (Debug:: * p)(std::string) = &Debug::Log;

				
				auto b = foo;
				//auto c = std::function<void>();

				void (*fp)(std::string str) = foo;

				using Fn = void(*)();
				using Fnp = void(**)();
				Fn fn = []() {  };

				void(*f)(std::string) = [](std::string s) {
					Script::engine->GetDebug()->Script(s);
				};

				auto af = static_cast<void(*)(std::string)>([](std::string s) {
					Script::engine->GetDebug()->Script(s);
				});
				//(void(*)(std::string))([](std::string s) {
				//	Script::engine->GetDebug()->Script(s);
				//	}
				*/
				//void (*a)(float x, float y, float z) = GameObject::Move;
				//void (SpaRcle::Engine::GameObject::*a)(bool b) = GameObject::SetActive;
				//void (SpaRcle::Engine::GameObject::*a)(float x, float y, float z) = GameObject::Move;
				//void (*a)(bool b) = GameObject::SetActive;
				//auto a = &GameObject::Move;
				
				luabridge::getGlobalNamespace(L)
					.beginClass<std::vector<pMaterial>>("Materials")
						.addConstructor<void(*) ()>()
						.addFunction("Add", (void (std::vector<pMaterial>::*)(const pMaterial & _Val)) & std::vector<pMaterial>::push_back)
					.endClass()

					.beginClass<SREngine>("Engine")
						.addStaticFunction("LoadPrefab", static_cast<GameObject*(*)(std::string)>([](std::string s) -> GameObject* {
								return engine->LoadPrefab(s); }))
					.endClass()

					.beginClass<Script>("Script")
					.endClass()

					.beginClass<World>("World")
						.addStaticFunction("Find", static_cast<GameObject*(*)(std::string)>([](std::string s) -> GameObject* {
							return Script::engine->GetCurrentWorld()->Find(s); }))
						.addStaticFunction("Instantiate", static_cast<GameObject*(*)(std::string, Model*)>([](std::string s, Model*model) -> GameObject* {
							return Script::engine->GetCurrentWorld()->Instantiate(s, model); }))
					.endClass()

					.beginClass<Material>("Material")
						.addStaticFunction("Load", static_cast<Material* (*)(std::string)>([](std::string s) -> Material* {
							return engine->GetRender()->GetMaterialManager()->LoadMaterial(s.c_str());
						}))
					.endClass()

					.beginClass<Model>("Model")
						.addStaticFunction("LoadOBJWithMats", static_cast<Model * (*)(std::string, std::vector<Material*>)>
							([](std::string s, std::vector<Material*> m) -> Model* 
						{
							return engine->GetRender()->GetModelManager()->LoadModelFromObj(s.c_str(), m);
						}))
						.addStaticFunction("LoadOBJ", static_cast<Model * (*)(std::string)> ([](std::string s) -> Model*  {
							return engine->GetRender()->GetModelManager()->LoadModelFromObj(s.c_str());
						}))
						.addStaticFunction("LoadOBJWithMat", static_cast<Model * (*)(std::string, Material*)> ([](std::string s, Material* mat) -> Model* {
							return engine->GetRender()->GetModelManager()->LoadModelFromObj(s.c_str(), { mat });
						}))
						//.addFunction("AddMaterial", static_cast<void(*)(Material*)>([](Material*m) {
							
						//}))
					.endClass()

					.beginClass<PointLight>("PointLight")
						.addStaticFunction("new", static_cast<PointLight * (*)()>([]() -> PointLight* { return new PointLight(); }))
						.addFunction("SetIntensity", &PointLight::SetIntensity)
					.endClass()

					.beginClass<DirectionalLight>("DirectionalLight")
						.addStaticFunction("new", static_cast<DirectionalLight * (*)()>([]() -> DirectionalLight* { return new DirectionalLight(); }))
					.endClass()

					.beginClass<GameObject>("GameObject")
						.addFunction("SetPosition", (void (SpaRcle::Engine::GameObject::*)(float x, float y, float z)) & GameObject::SetPosition)
						.addFunction("SetRotation", (void (SpaRcle::Engine::GameObject::*)(float x, float y, float z)) & GameObject::SetRotation)
						.addFunction("SetScale", (void (SpaRcle::Engine::GameObject::*)(float x, float y, float z)) & GameObject::SetScale)
						.addFunction("Move",   (void (SpaRcle::Engine::GameObject::*)(float x, float y, float z) )&GameObject::Move)
						.addFunction("Rotate", (void (SpaRcle::Engine::GameObject::*)(float x, float y, float z) )&GameObject::Rotate)
							.addFunction("AddPointLight", (void(GameObject::*)(PointLight*)) & GameObject::AddComponent<PointLight*>)
							.addFunction("AddDirectionalLight", (void(GameObject::*)(DirectionalLight*)) & GameObject::AddComponent<DirectionalLight*>)
					.endClass()

					.beginClass<Debug>("Debug")
						.addStaticFunction("Log", static_cast<void(*)(std::string)>([](std::string s) {
							Script::engine->GetDebug()->Script(s); }))
						.addStaticFunction("Log", static_cast<void(*)(double)>([](double s) {
							Script::engine->GetDebug()->Script(std::to_string(s)); }))
						.addStaticFunction("Log", static_cast<void(*)(int)>([](int s) {
							Script::engine->GetDebug()->Script(std::to_string(s)); }))

						.addStaticFunction("Error", static_cast<void(*)(std::string)>([](std::string s) {
							Script::engine->GetDebug()->ScriptError(s);
						}))
					.endClass()
					//?========================

					//.beginClass<Test>("Test")
					//	.addConstructor<void(*) ()>()
						//.addFunction("Log", &Test::Log)
					//.endClass();
					;
				return false;
			}
			bool Script::RegisterStandartVariables() {
				return false;
			}
			bool Script::Compile(SREngine* engine, Debug* debug) {
				if (!isCompile) {
					if(!this->engine) this->engine = engine;
					this->debug  = debug;

					lua_script = String::MakePath(engine->GetResourcesFolder() + "\\Scripts\\" + lua_script + ".lua");

					L = luaL_newstate();

					r = luaL_loadfile(L, lua_script.c_str());
					if (r != 0) /* //|| lua_pcall(lua_state, 0, 0, 0)) */ {
						std::string reason;

						switch (r) {
						case LUA_ERRFILE:
							reason = "Can not open file!";
							break;
						case LUA_ERRSYNTAX:
							/* http://www.lua.ru/forum/posts/list/362.page */
							reason = std::string(lua_tostring(L, -1));
							break;
						case LUA_ERRMEM:
							reason = "Not enough memory!";
							break;
						default:
							reason = "Unknown reason!";
							break;
						}

						debug->ScriptError("Failed compile : " + lua_script + "\n\tReason : " + reason);
						return false;
					}
					
					/* Незнамо зачем, но так надо (http://www.gamedev.ru/code/forum/?id=125829) */
					lua_pcall(L, 0, 0, 0);

					debug->Script("Compile : " + lua_script);
					
					if(true)
					{ //?================ INIT LUA ================ 
						static const luaL_Reg lualibs[] = {
							{"base", luaopen_base},
							{"io", luaopen_io},
							{"math", luaopen_math },
							{NULL, NULL}
						};

						for (const luaL_Reg* lib = lualibs; lib->func != NULL; lib++) {
							luaL_requiref(L, lib->name, lib->func, 1);
							lua_settop(L, 0);
						}
					} //?================ INIT LUA ================

					this->RegisterStandartFunctions();
					this->RegisterStandartVariables();

					isCompile = true;
					return true;
				} else return false;
			}

			Script::Script(std::string lua_script) : lua_script(lua_script) {
				this->L  = nullptr;
				this->isCompile  = false;
			}
			Script::~Script() {
				Close();
			}

			bool Script::Init() {

				return false;
			}
			bool Script::Start() {
				if (isCompile) {
					r = lua_getglobal(L, "Start");
					if (lua_pcall(L, 0, 0, 0)) {
						debug->ScriptError("Filed call \"Start()\"! File " + this->lua_script);
						return false;
					}
					return true;
				}
				else {
					debug->ScriptError("Script::Start() : file is not compiled!\n\t" + lua_script);
					return false;
				}
			}
			bool Script::Update(float time) {
				if (isCompile) {
					//luaL_dofile(lua_state, lua_script.c_str());
					//int r = lua_getfield(lua_state, LUA_REGISTRYINDEX, "Update");
					//std::cout << r << std::endl;

					r = lua_getglobal(L, "Update");

					lua_pushnumber(L, time);
					lua_setglobal(L, "Time");

					if (lua_pcall(L, 0, 0, 0)) {
						debug->ScriptError("Run-time error! File " + this->lua_script);
						this->hasErrors = true;
						Sleep(100);
						return false;
					}

					//std::cout << r << std::endl;
					//lua_settop(L, 0);
					//lua_getfield(L, LUA_GLOBALSINDEX, "lua_test");
					//lua_pushstring(L, "aaa");
					//lua_pushinteger(L, 1000);
					//r = lua_pcall(L, 2 /* num args */, 1 /* num res */, 0);
					//if (r != 0)
					//{
					//	fprintf(stderr, "Run-time Lua error: %s\n", lua_tostring(L, -1));
					//}

					return true;
				}
				else { 
					debug->ScriptError("Script::Update() : file is not compiled!\n\t" + lua_script);
					return false; 
				}
			}
			bool Script::Close() {
				lua_close(L);
				return true;
			}
		}
	}
}