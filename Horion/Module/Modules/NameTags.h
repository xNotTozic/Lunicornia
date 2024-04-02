#pragma once

#include "Module.h"
#include "../../DrawUtils.h"
#include "../../../Utils/Target.h"

class NameTags : public IModule
{
public:
	bool displayHealth = true;
	bool useUnicodeFont = false;
	NameTags();
	~NameTags();

	// Inherited via IModule
	virtual const char* getModuleName() override;
	virtual void onPostRender() override;
};

