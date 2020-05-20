#pragma once
#include <string>
#include <TCP.h>
#include <thread>
#include <Debug.h>
#include "Settings.h"

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

		std::string core_name;
	public:
		Core(std::string core_name, TCP* tcp, Debug* debug, Settings* settings) 
			: core_name(core_name), tcp(tcp), settings(settings), debug(debug)
		{
			isRun = false; 
			task = std::thread();
		}
		~Core() { Close(); }
	public:
		virtual void* GetData() { return nullptr; } ///$TODO
	protected:
		virtual bool Start() { return false; };
		virtual bool Update() { return false; };
		virtual bool Completed() { return false; };
	public:
		bool Init() {
			debug->Info("Initializing core \"" + core_name + "\"...");
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