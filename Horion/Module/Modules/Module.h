#pragma once

#include "../../../Utils/Utils.h"
#include "../../../Memory/GameData.h"
#include "../../../Utils/Json.hpp"
#include "../../FriendList/FriendList.h"
#include <string>

using json = nlohmann::json;

enum class Category {
	COMBAT,
	VISUAL,
	MOVEMENT,
	BUILD,
	EXPLOITS,
	AUTO,
	TROLLS
};

enum class ValueType {
	FLOAT_T,
	DOUBLE_T,
	INT64_T,
	INT_T,
	BYTE,
	BOOL_T,
	TEXT_T
};

struct SettingValue {
	union {
		float _float;
		double _double;
		__int64 int64;
		int _int;
		bool _bool;
		std::string* text;
	};
};

struct SettingEntry {
	char name[0x20] = "";
	ValueType valueType;
	SettingValue* value = nullptr;
	SettingValue* defaultValue = nullptr;
	SettingValue* minValue = nullptr;
	SettingValue* maxValue = nullptr;

	// ClickGui Data
	bool isDragging = false; // This is incredibly hacky and i wanted to avoid this as much as possible but i want to get this clickgui done

	void makeSureTheValueIsAGoodBoiAndTheUserHasntScrewedWithIt() {
		switch (valueType) {
		case ValueType::TEXT_T:
		case ValueType::BOOL_T:
			break;
		case ValueType::INT64_T:
			value->int64 = max(minValue->int64, min(maxValue->int64, value->int64));
			break;
		case ValueType::DOUBLE_T:
			value->_double = max(minValue->_double, min(maxValue->_double, value->_double));
			break;
		case ValueType::FLOAT_T:
			value->_float = max(minValue->_float, min(maxValue->_float, value->_float));
			break;
		case ValueType::INT_T:
			value->_int = max(minValue->_int, min(maxValue->_int, value->_int));
			break;
		default:
			logF("unrecognized value %i", valueType);
		}
	}
};

class IModule
{
public:
	bool enabled = false;
	int keybind = 0x0;
	bool extended = false;
	Category category;
	const char* tooltip;

	bool isPremium = false;

	std::vector<SettingEntry*> settings;
protected:
	IModule(int key, Category c, const char* tooltip);
	IModule(int key, Category c, const char* tooltip, bool isPremium);

	void registerFloatSetting(std::string name, float* floatPtr, float defaultValue, float minValue, float maxValue);
	void registerIntSetting(std::string name, int* intpTr, int defaultValue, int minValue, int maxValue);
	void registerByteSetting(std::string name, int* intPtr, int defaultValue, int minValue, int maxValue);
	void registerBoolSetting(std::string name, bool* boolPtr, bool defaultValue);
public:
	unsigned short hoverTime;
	~IModule();

	const Category getCategory() { return category; };

	inline std::vector<SettingEntry*>* getSettings() { return &settings; };

	virtual const char* getModuleName() = 0;
	virtual const char* getRawModuleName();
	virtual int getKeybind();
	virtual void setKeybind(int key);
	virtual bool allowAutoStart();

	virtual void onTick(C_GameMode*);
	virtual void onKeyUpdate(int key, bool isDown);
	virtual void onEnable();
	virtual void onDisable();
		    void reEnable();
	virtual void onPreRender();
	virtual void onPostRender();
	virtual void onLoadConfig(json* conf);
	virtual void onSaveConfig(json* conf);
	virtual bool isFlashMode();
	virtual void setEnabled(bool enabled);
	virtual void toggle();
	virtual bool isEnabled();
	virtual void onSendPacket(C_Packet*);
	const char* getTooltip();
};

