#include "pch.h"
#include "Causality.h"
#include "Core.h"

bool SpaRcle::Causality::AddCore(Core* core) {
	if (!isRun) { debug->Error("Causality is not running!"); return false; }

	for (CausalCoreData& ccd : cores_data)
		if (ccd.core_name == core->GetName()) {
			debug->Error("Causality::AddCore() : core \"" + ccd.core_name + "\" already exists!");
			return false;
		}

	cores_data.push_back(CausalCoreData(core->GetName()));

	return true;
}
