#pragma once
#include <string>
#include <SRHelper.h>
#include <vector>
#include "Neuron.h"
#include "ISystem.h"
#include <map>

namespace SpaRcle {
	class Core;

	class Causality : public ISystem {
		class CausalCoreData {
		public:
			CausalCoreData(std::string core_name) { //, unsigned short count
				this->core_name = core_name;
				//this->count = count; // забыл зачем это...
				n_adress = std::vector<Neuron*>();
				n_names = std::vector<std::string>();
			}
			void Destroy() {
				//count = 0;
				n_adress.clear();
				n_names.clear();
				core_name.clear();
			}
		public:
			std::string			   core_name;
			std::vector<Neuron*>	n_adress;
			std::vector<std::string> n_names;
			//unsigned short		   count;
		};
		//!---------------------------------------------------------------------
	public:
		Causality(Debug* debug, Settings* settings, FileManager* fileManager) : ISystem(debug, settings, fileManager) {

		}
		~Causality() { Close(); }
	public:
		bool Run() override {
			//!!!!!!!!!!!!!!!!!!!!



			//!!!!!!!!!!!!!!!!!!!!

			isRun = true;

			debug->System("Causality has been started!");

			return true;
		}
		bool Close() override {
			isRun = false;

			for (CausalCoreData& ccd : cores_data) {
				ccd.Destroy();
			}

			debug->System("Causality has been stopped!");

			return true;
		}
	private:
		std::vector<CausalCoreData> cores_data = std::vector<CausalCoreData>();
		std::map<std::string, Neuron*> Perhaps = std::map<std::string, Neuron*>();
	public:
		Neuron* GetPerhap(const std::string& name) {
			auto find = Perhaps.find(name);
			if (find == Perhaps.end())
				return nullptr;
			else return find->second;
		}
		bool AddCore(Core* core);
		//bool Remember(std::string core_name, std::string n_name, IKernel* kernel_data) {
			///$TODO n_data
		//}
	};
}

