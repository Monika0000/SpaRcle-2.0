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
		IKernel* kernel;				// ���� �������, ������ ��� ������
	public:
		//Vector3 position;
		unsigned long usings;
		Dendrite* dendr;
		Akson* akson;					///%���������
		std::vector<Synapse*> Synapses;	///%�������
	};
}

