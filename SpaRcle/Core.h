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

namespace SpaRcle {
	using namespace Network;

	class Core {
	private:
		std::thread task;
		bool isRun;
	protected:
		bool IsRun() const { return isRun; }

		TCP* tcp;
		Debug* debug;
		Settings* settings;
		FileManager* file_manager;

		Logicality* logic;
		Causality* causality;

		std::string core_name;
	public:
		Core(std::string core_name, TCP* tcp, Debug* debug, Settings* settings, FileManager*file_manager) 
			: core_name(core_name), tcp(tcp), settings(settings), debug(debug), file_manager(file_manager)
		{
			isRun = false; 
			task = std::thread();
			logic = nullptr;
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
		bool Init(Logicality* logic, Causality* causality) {
			debug->Info("Initializing core \"" + core_name + "\"...");

			if (!logic) { debug->Error("Logicality in core \"" + core_name + "\" is nullprt!"); return false; } else this->logic = logic;
			if (!causality) { debug->Error("Causality in core \"" + core_name + "\" is nullprt!"); return false; } else this->causality = causality;

			return Start();
		};
		bool Run() { 
			if (!isRun) {
				debug->Info("Running core \"" + core_name + "\"...");

				isRun = true;

				tcp->Run();

				task = std::thread([this]() {
					while (isRun)
						if (!Update())
							break;
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