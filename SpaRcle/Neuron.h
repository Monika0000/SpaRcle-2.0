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
			������ ��������� ������������ ��� �������� �������� ������ ������ �������
			Save - ���������� ���������� � ���� ������, ������� ����� ��������� � ����
			Load - ��������� �� ����� ������ � �������������� ��, "���������" ������ ������ ����
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
		IKernel* kernel;				// ���� �������, ������ ��� ������
	public:
		//Vector3 position;
		unsigned long usings;
		Dendrite* dendr;
		Akson* akson;					///%���������
		std::vector<Synapse*> Synapses;	///%�������
	};
}

