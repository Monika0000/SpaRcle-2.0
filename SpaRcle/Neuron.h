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

	struct Synapse {
	public:
		Synapse(char* name, Neuron* neuron) {
			this->name = name;
			this->neuron = neuron;
		};
		~Synapse() { 
			delete[] name; //TODO: Может вызвать ошибки!!!
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
	//public:
		//bool Save(std::ofstream file) override { return false; }
		//bool Load(std::ifstream file) override { return false; }
	public:
		unsigned long usings;
		Dendrite* dendr;
		Akson* akson;					///%Следствия
		std::vector<Synapse*> Synapses;	///%Причины
	};
}

