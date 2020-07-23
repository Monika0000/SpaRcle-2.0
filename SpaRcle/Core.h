#pragma once
#include <string>
#include <TCP.h>
#include <thread>
#include <Debug.h>
#include "Settings.h"
#include "Logicality.h"
#include "Causality.h"
#include <FileManager.h>
#include "Neuron.h"
#include <functional>
#include "Hippocampus.h"

namespace SpaRcle {
	using namespace Network;

	class Core {
	private:
		std::thread task;
		bool isRun;
		bool isWaitPackage;
	protected:
		bool isCanGetKernelPackages;
		bool HasPackages() { 
			if (isWaitPackage) {
				isWaitPackage = false;
				return true;
			}
			else return false;
			//return !isWaitPackage; 
		}
	protected:
		bool IsRun() const { return isRun; }

		TCP* tcp;
		Debug* debug;
		Settings* settings;
		FileManager* file_manager;

		Logicality* logic;
		Causality* causality;
		Hippocampus* hippocampus;

		std::string core_name;
	public:
		Core(std::string core_name, TCP* tcp, Debug* debug, Settings* settings, FileManager*file_manager) 
			: core_name(core_name), tcp(tcp), settings(settings), debug(debug), file_manager(file_manager) //new IKernel*[1000] std::vector<IKernel*>()
		{
			isRun = false; 
			task = std::thread();
			hippocampus = nullptr;
			logic = nullptr;
			isWaitPackage = true;
		}
		~Core() { Close(); }
		const std::string GetName() const { return core_name; }
	public:
		virtual void* GetData() { return nullptr; } ///$TODO
	protected:
		virtual bool Start() { return false; };
		virtual bool Update() { return false; };
		virtual bool Completed() { return false; };
	public:
		bool Init(Logicality* logic, Causality* causality, Hippocampus* hippocampus) {
			debug->Info("Initializing core \"" + core_name + "\"...");

			if (!logic) { debug->Error("Logicality in core \"" + core_name + "\" is nullprt!"); return false; } else this->logic = logic;
			if (!causality) { debug->Error("Causality in core \"" + core_name + "\" is nullprt!"); return false; } else this->causality = causality;

			this->hippocampus = hippocampus;

			return Start();
		};
		bool Run() { 
			if (!isRun) {
				debug->Info("Running core \"" + core_name + "\"...");

				isRun = true;
				
				if (!tcp->Run()) { debug->Error("Failed running core \"" + core_name + "\"! TCP client-server return false."); return false; }

				task = std::thread([this]() {
					Sleep(1);

					while (isRun) {
						if (isWaitPackage) {
							//if (tcp->GetState() == PackState::End)
							//	tcp->Recv();
							//else
							//	if (tcp->GetState() == PackState::Begin)
							//		isWaitPackage = true;

							//if(tcp->GetState() == PackState::End && isCanGetKernelPackages) isWaitPackage = false;
						}

						if (!Update())
							break;
					}
					debug->Info("Core \"" + core_name + "\" has been completed working.");
				});

				return true;
			}
			else { 
				debug->Error("Core already runned!");
				return false; 
			}
		};
		bool Close();
	};
}