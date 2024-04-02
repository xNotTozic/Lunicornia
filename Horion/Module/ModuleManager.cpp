#include "ModuleManager.h"

ModuleManager::ModuleManager(GameData * gameData)
{
	this->gameData = gameData;
}

ModuleManager::~ModuleManager()
{
	initialized = false;
	for (int i = 0; i < this->moduleList.size(); i++)
	{
		delete this->moduleList[i];
	}
}

void ModuleManager::initModules()
{
	this->moduleList.push_back(new HudModule());
	this->moduleList.push_back(new Killaura());
	this->moduleList.push_back(new ESP());
	this->moduleList.push_back(new Jetpack());
	this->moduleList.push_back(new Aimbot());
	this->moduleList.push_back(new TriggerBot());
	this->moduleList.push_back(new ChestESP());
	this->moduleList.push_back(new NoKnockBack());
	this->moduleList.push_back(new RainbowSky());
	this->moduleList.push_back(new AirJump());
	this->moduleList.push_back(new Step());
	this->moduleList.push_back(new Glide());
	this->moduleList.push_back(new EditionFaker());
	this->moduleList.push_back(new Phase());
	this->moduleList.push_back(new Freecam());
	this->moduleList.push_back(new AutoSprint());
	this->moduleList.push_back(new Tracer());
	this->moduleList.push_back(new BowAimbot());
	this->moduleList.push_back(new Scaffold());
	this->moduleList.push_back(new NoFall());
	this->moduleList.push_back(new Blink());
	this->moduleList.push_back(new Nuker());
	this->moduleList.push_back(new InstaBreak());
	this->moduleList.push_back(new NoPacket());
	this->moduleList.push_back(new Speed());
	this->moduleList.push_back(new Xray());
	this->moduleList.push_back(new BedFucker());
	this->moduleList.push_back(new NoSlowDown());
	this->moduleList.push_back(new AutoTotem());
	this->moduleList.push_back(new InfiniteReach());
	this->moduleList.push_back(new ClickGuiMod());
	this->moduleList.push_back(new ChestStealer());
	this->moduleList.push_back(new Fly());
	this->moduleList.push_back(new Hitbox());
	this->moduleList.push_back(new Reach());
	this->moduleList.push_back(new FullBright());
	this->moduleList.push_back(new AirSwim());
	this->moduleList.push_back(new InventoryMove());
	this->moduleList.push_back(new HighJump());
	this->moduleList.push_back(new NoWeb());
	this->moduleList.push_back(new FastLadder());
	this->moduleList.push_back(new StackableItem());
	this->moduleList.push_back(new FastEat());
	this->moduleList.push_back(new Jesus());
	this->moduleList.push_back(new AutoArmor());
	this->moduleList.push_back(new InfiniteBlockReach());
	this->moduleList.push_back(new AutoClicker());
	this->moduleList.push_back(new NameTags());
	this->moduleList.push_back(new Criticals());
	this->moduleList.push_back(new Bhop());
	this->moduleList.push_back(new BugUp());
	this->moduleList.push_back(new MidClick());
	this->moduleList.push_back(new ClickTP());
	this->moduleList.push_back(new NoFriends());
	this->moduleList.push_back(new Spammer());
	this->moduleList.push_back(new ChestAura());
	this->moduleList.push_back(new AntiBot());
	this->moduleList.push_back(new InventoryCleaner());
	this->moduleList.push_back(new Derp());
	this->moduleList.push_back(new PacketLogger());
	this->moduleList.push_back(new SmoothFont());
	this->moduleList.push_back(new NoHitbox());
	this->moduleList.push_back(new Tower());

	// Sort module alphabetically
	std::sort(moduleList.begin(), moduleList.end(), [](const IModule* lhs, const IModule* rhs)
	{
		IModule* current = const_cast<IModule*>(lhs);
		IModule* other = const_cast<IModule*>(rhs);
		return std::string{ *current->getModuleName() } < std::string{ *other->getModuleName() };
	});

	initialized = true;

	this->getModule<HudModule>()->setEnabled(true);
	this->getModule<ClickGuiMod>()->setEnabled(true);
	this->getModule<AntiBot>()->setEnabled(true);
}

void ModuleManager::disable()
{
	for (std::vector<IModule*>::iterator it = this->moduleList.begin(); it != this->moduleList.end(); ++it) {
		IModule* mod = *it;
		if (mod->isEnabled())
			mod->setEnabled(false);
	}
}

void ModuleManager::onLoadConfig(json * conf)
{
	if (!isInitialized())
		return;

	for (int i = 0; i < this->moduleList.size(); i++)
		this->moduleList[i]->onLoadConfig(conf);
}

void ModuleManager::onSaveConfig(json * conf)
{
	if (!isInitialized())
		return;
	for (std::vector<IModule*>::iterator it = this->moduleList.begin(); it != this->moduleList.end(); ++it) {
		IModule* mod = *it;
		mod->onSaveConfig(conf);
	}
}

void ModuleManager::onTick(C_GameMode * gameMode)
{
	if (!isInitialized())
		return;
	for (std::vector<IModule*>::iterator it = this->moduleList.begin(); it != this->moduleList.end(); ++it) {
		IModule* mod = *it;
		if (mod->isEnabled())
			mod->onTick(gameMode);
	}
}

void ModuleManager::onKeyUpdate(int key, bool isDown)
{
	if (!isInitialized())
		return;
	for (std::vector<IModule*>::iterator it = this->moduleList.begin(); it != this->moduleList.end(); ++it) {
		IModule* mod = *it;
		mod->onKeyUpdate(key, isDown);
	}
}

void ModuleManager::onPreRender()
{
	if (!isInitialized())
		return;
	for (std::vector<IModule*>::iterator it = this->moduleList.begin(); it != this->moduleList.end(); ++it) {
		IModule* mod = *it;
		if (mod->isEnabled())
			mod->onPreRender();
	}
}

void ModuleManager::onPostRender()
{
	if (!isInitialized())
		return;
	for (std::vector<IModule*>::iterator it = this->moduleList.begin(); it != this->moduleList.end(); ++it) {
		IModule* mod = *it;
		if (mod->isEnabled())
			mod->onPostRender();
	}
}

void ModuleManager::onSendPacket(C_Packet* packet)
{
	if (!isInitialized())
		return;
	for (auto it : moduleList) {
		if (it->isEnabled())
			it->onSendPacket(packet);
	}
}

std::vector<IModule*>* ModuleManager::getModuleList()
{
	return &this->moduleList;
}

int ModuleManager::getModuleCount()
{
	return (int)(&moduleList)->size();
}

int ModuleManager::getEnabledModuleCount()
{
	int i = 0;
	for (auto it = (&moduleList)->begin(); it != (&moduleList)->end(); ++it) {
		IModule* mod = *it;
		if ((*it)->isEnabled()) i++;
	}
	return i;
}

ModuleManager* moduleMgr = new ModuleManager(&g_Data);
