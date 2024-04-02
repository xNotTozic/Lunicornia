#pragma once

#include "../../../Utils/Target.h"
#include "../../DrawUtils.h"
#include "Module.h"

class ESP : public IModule {
public:
	bool isMobEsp = false;
	bool doRainbow = true;
	ESP();
	~ESP();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender() override;
};
