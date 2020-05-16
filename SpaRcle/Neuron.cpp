#include "pch.h"
#include "Neuron.h"

namespace SpaRcle {
	SpaRcle::Neuron::Neuron() {
		dendr = new Dendrite(0.f, 0.f);
		position = Vector3 { 0.f, 0.f , 0.f };
		akson = nullptr;
		this->Synapses = std::vector<Synapse*>();
	}
	
	SpaRcle::Neuron::~Neuron() {
		if (dendr) delete dendr;
		if (akson) delete akson;
	}
}
