#pragma once
#include <FileManager.h>
#include <Debug.h>
#include "Settings.h"
#include <string>
#include <vector>

namespace SpaRcle {
	using namespace Helper;

	class Neuron;

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
		Neuron();
		~Neuron();
	public:
		Dendrite* dendr;
		Akson* akson;					///%Следствия
		std::vector<Synapse*> Synapses;	///%Причины
	};
}

