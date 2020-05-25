#pragma once
#include <Neuron.h>
#include <TCP.h>

using namespace SpaRcle;
using namespace SpaRcle::Helper;
using namespace SpaRcle::Network;

class MoveKernel : public IKernel, public IPackage {
public:
	MoveKernel() {
		boneRotation = nullptr;
		boneName = std::string();
		isNew = false;
	}
	~MoveKernel() {
		delete boneRotation;
	}
private:
	std::string Get()  { 
		if (boneRotation) 
			return boneName + ";" + boneRotation->GetString();
		else {
			Debug::InternalError("MoveKernel::Get() : boneRotation is nullptr!");
			return "none";
		} 
	}
	bool Set(std::string& data) {
		size_t index = 0;
		size_t end = 0;
		size_t default_size = data.size() - 1;
		
		if (String::ReadToChar(data, '[', 0, &index) == "add_bone") isNew = true;

		data = String::ReadToChar(data, ']', index + 1, &end);

		if (end < default_size) Debug::InternalWarning("MoveKernel::Set() : There is extra data that is not used!\n\tEnd = " + 
			std::to_string(end) + "\n\tSize = " + std::to_string(default_size));

		boneName = String::ReadToChar(data, ';', 0, &index);
		data = data.substr(index + 1);

		boneRotation = Vector3::FromString(data);

		return (bool)boneRotation;
	}
public:
	/*
		“екущий поворот кости, либо поворот к которому необходимо стремитьс€
	*/
	bool isNew;
	std::string boneName;
	Vector3* boneRotation;
public:
	//!---------------------[IPackage]--------------------
	std::string GetSendData() override {
		return Get();
	}
	bool SetData(std::string data) override {
		//std::cout << "MoveKernel::SetData() : " << data << std::endl;
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