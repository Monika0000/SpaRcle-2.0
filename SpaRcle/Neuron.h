#pragma once
#include <FileManager.h>
#include <Debug.h>
#include "Settings.h"
#include <string>
#include <vector>
#include <Vector3.h>

namespace SpaRcle {
	using namespace Helper;

	class Neuron;

	__interface IKernel {
		/*
			Данный интерфейс предназначен для описания хранимых данных внутри нейрона
			Save - возвращает содержимое в виде строки, которую можно сохранить в файл
			Load - принимает ту самую строку и расшифровывает ее, "запихивая" данные внутрь себя
		*/
	public:
		virtual std::string Save() = 0;// { return ""; }
		virtual bool  Load(std::string data) = 0;// { return 0; }
	};

	struct Synapse {
	public:
		Synapse(char* name, Neuron* neuron) {
			this->name = name;
			this->neuron = neuron;
		};
		~Synapse() { 
			delete[] name;
			this->neuron = nullptr;
		};
	public:
		char* name;
		Neuron* neuron;
	};
	
	class Akson {
	public:
		Akson() {
			this->names = std::vector<char*>();
			this->neurons = std::vector<Neuron*>();
		}
		~Akson() {
			for (size_t t = 0; t < names.size(); t++) {
				delete[] names[t];
			}
			this->names.clear();
			this->neurons.clear();
		}
	public:
		std::vector<char*>		 names;
		std::vector<Neuron*>	 neurons;
	};

	struct Dendrite {
	public:
		Dendrite(float bad, float good) {
			this->bad  = bad; 
			this->good = good;
		}
		float bad, good;
	};

	class Neuron : public ISavable {
	public:
		Neuron();
		~Neuron();
	public:
		bool Save(std::ofstream file) override { return false; }
		bool Load(std::ifstream file) override { return false; }
	public:
		IKernel* kernel;				// Ядро нейрона, хранит его данные
	public:
		//Vector3 position;
		unsigned long usings;
		Dendrite* dendr;
		Akson* akson;					///%Следствия
		std::vector<Synapse*> Synapses;	///%Причины
	};
}

