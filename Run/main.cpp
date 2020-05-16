#include <iostream>
#include <SRFramework.h>
#include <SRHelper.h>

#include "Vision.h"

using namespace SpaRcle;
using namespace SpaRcle::Helper;

int main() {
	Settings* settings = new Settings();
	Debug* debug = new Debug(settings->GetPath());

	SRFramework* framework = new SRFramework(debug, settings);
	framework->Create();

	framework->SetTCP(new TCP("localhost", 1111, debug));

	Vision* vision = new Vision();
	framework->LoadCore(vision);

	framework->Init();
	framework->Run();
	framework->Close();
}