#pragma once
#include <Neuron.h>
#include <TCP.h>

using namespace SpaRcle;
using namespace SpaRcle::Helper;
using namespace SpaRcle::Network;

class MoveKernel : public IKernel, public IPackage {
public:
	MoveKernel() {

	}
	~MoveKernel() {
		delete boneRotation;
	}
private:
	inline const std::string& Get() { return boneRotation->GetString(); }
	inline const bool Set(std::string& data) { 
		boneRotation = Vector3::FromString(data); 
		return (bool)boneRotation;
	}
public:
	/*
		“екущий поворот кости, либо поворот к которому необходимо стремитьс€
	*/
	Vector3* boneRotation;
public:
	//!---------------------[IPackage]--------------------
	std::string GetSendData() override {
		return Get();
	}
	bool SetData(std::string data) override {
		std::cout << "MoveKernel::SetData() : " << data << std::endl;
		return Set(data);
	}
	//!---------------------[IPackage]--------------------



	//!---------------------[IKernel]--------------------
	std::string Save() override {
		return Get();
	}
	bool Load(std::string data) override {
		return Set(data);
	}
	//!---------------------[IKernel]--------------------
};