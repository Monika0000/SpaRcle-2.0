#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Neuron.h>
#include <TCP.h>

using namespace SpaRcle;
using namespace SpaRcle::Helper;
using namespace SpaRcle::Network;

struct MoveKernel : public IKernel, public IPackage {
public:
	MoveKernel() {
		boneRotation = nullptr;
		//boneName = nullptr;
		isNew = false;
	}
	~MoveKernel() {
		if (boneRotation) delete boneRotation;
		//if (boneName) delete[] boneName;
	}
private:
	std::string Get()  { 
		if (boneRotation) 
			return std::string(name) + ";" + boneRotation->GetString();
		else {
			Debug::InternalError("MoveKernel::Get() : boneRotation is nullptr!");
			return "none";
		} 
	}
	/*
	char* CopyString(std::string& str) {
		//char* sp = (char*)str.c_str();

		//char* rs = new char[sizeof(sp)];
		//for (size_t t = 0; t < sizeof(sp); t++)
		//	sp[t] = sp[t];

		char* rs = new char[str.size() + 1];
		strcpy(rs, str.c_str());

		return rs;
	}
	*/
	bool Set(std::string& data) {
		size_t index = 0;
		size_t end = 0;
		size_t default_size = data.size() - 1;
		
		//boneName = String::CopyStringToCharPointer(data);
		//boneRotation = new Vector3{ 0,0,0 };

		if (String::ReadToChar(data, '[', 0, &index) == "add_bone") isNew = true;

		data = String::ReadToChar(data, ']', index + 1, &end);

		if (end < default_size) Debug::InternalWarning("MoveKernel::Set() : There is extra data that is not used!\n\tEnd = " + 
			std::to_string(end) + "\n\tSize = " + std::to_string(default_size));

		//boneName = String::ReadToChar(data, ';', 0, &index);
		name = String::CopyStringToCharPointer(String::ReadToChar(data, ';', 0, &index));
		data = data.substr(index + 1);

		boneRotation = Vector3::FromString(data);

		return (bool)boneRotation;
	}
public:
	/*Если данная кость новая. В основном только при инициализации*/
	bool isNew;

	/*Имя кости. Нейронам дается такое же название*/
	//char* boneName;
	
	/*Текущий поворот кости, либо поворот к которому необходимо стремиться*/
	Vector3* boneRotation;
public:
	//!---------------------[IPackage]--------------------
	std::string GetSendData() override { return Get(); }
	bool SetData(std::string data) override { return Set(data); }
	//!---------------------[IPackage]--------------------

	//!---------------------[IKernel]--------------------
	std::string Save() override { return Get(); }
	bool Load(std::string data) override { return Set(data); }
	MoveKernel* Copy() {
		MoveKernel* new_kernel_move = new MoveKernel();

		if (this->name) new_kernel_move->name = String::CopyChars(this->name);
		if (this->boneRotation) new_kernel_move->boneRotation = Vector3::Copy(this->boneRotation);
		new_kernel_move->isNew = this->isNew;

		return new_kernel_move;
	}
	//!---------------------[IKernel]--------------------
};