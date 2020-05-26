#include "pch.h"
#include "Hippocampus.h"

SpaRcle::Hippocampus::Hippocampus() {
	this->debug = nullptr;
	this->settings = nullptr;
	this->file_manager = nullptr;
	this->path = std::string();
	this->file = std::ofstream();
}

SpaRcle::Hippocampus::~Hippocampus() { Close(); }

bool SpaRcle::Hippocampus::Create(Debug* debug, Settings* settings, FileManager* file_manager) {
	if (!debug) { Debug::InternalError("Hippocampus::Create() : debug is nullptr!"); return false; } else this->debug = debug;

	debug->Info("Creating hippocampus...");

	if (!settings) { debug->Error("Hippocampus::Create() : settings is nullptr!"); return false; } else this->settings = settings;

	if (!file_manager) { debug->Error("Hippocampus::Create() : file manager is nullptr!"); return false; } else this->file_manager = file_manager;

	isCreate = true;

	return true;
}

bool SpaRcle::Hippocampus::Init() {
	debug->Info("Initializing hippocampus...");

	if (!isCreate) { debug->Error("Memory is not create!"); return false; }

	isInit = true;

	return true;
}

bool SpaRcle::Hippocampus::Run() {
	debug->Info("Running hippocampus...");

	if (!isInit) { debug->Error("Hippocampus is not initialize!"); return false; }

	isRun = true;

	return true;
}

bool SpaRcle::Hippocampus::Close() {
	debug->Info("Close hippocampus...");

	isRun = false;

	return true;
}
