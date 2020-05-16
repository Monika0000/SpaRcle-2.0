#include "pch.h"
#include "Neuron.h"

namespace SpaRcle {
	SpaRcle::Neuron::Neuron() {
		dendr = new Dendrite(0.f, 0.f);
	}
	
	SpaRcle::Neuron::~Neuron() {
		if (dendr) delete dendr;
	}
}
