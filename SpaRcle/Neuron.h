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
		virtual std::string Save() = 0;
		virtual bool Load(std::string data) = 0;
	};

	class Synapse {
	public:
		Synapse(std::string name, Neuron* neuron) { 
			this->name = name;
			this->neuron = neuron;
		};
		~Synapse() { 
			this->name.clear();
			this->neuron = nullptr;
		};
	public:
		std::string name;
		Neuron* neuron;
	};
	
	class Akson {
	public:
		Akson() {
			this->names = std::vector<std::string>();
			this->neurons = std::vector<Neuron*>();
		}
		~Akson() {
			this->names.clear();
			this->neurons.clear();
		}
	public:
		std::vector<std::string> names;
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

	class Neuron {
	public:
		Neuron(IKernel* kernel);
		~Neuron();
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

