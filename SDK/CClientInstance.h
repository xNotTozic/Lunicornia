#pragma once

#include "CEntity.h"
#include "CGameSettingsInput.h"
#include "CLoopbackPacketSender.h"
#include "TextHolder.h"
#include "CMinecraftUIRenderContext.h"

class Minecraft;

class LevelRendererPlayer {
public:
	BUILD_ACCESS(this, vec3_t, origin, 0x514); // Updated
};

class LevelRenderer {
public:
	BUILD_ACCESS(this, LevelRendererPlayer*, levelRendererPlayer, 0x2F8); // Updated

	vec3_t getOrigin() {
		return levelRendererPlayer->origin;
	}
};
class HitDetectSystem;

struct C_FontRepository_FontList_FontEntry {
public:
	C_Font* font;

private:
	void* sharedFontPtr;
};

struct C_FontRepository_FontList
{
public:
	C_FontRepository_FontList_FontEntry fontEntries[9];
};


struct C_FontRepository
{
private:
	uintptr_t* font_repository_vtable;  // 0x0000
	__int64 pad;                        // 0x0008
	void* ptrToSelf;                    // 0x0010
	void* ptrToSelfSharedPtr;           // 0x0018
public:
	C_FontRepository_FontList* fontList;  // 0x0020
	//FontRepository_FontList* fontList1;  //0x0028
};

class MinecraftGame {
public:
	BUILD_ACCESS(this, bool, canUseKeys, 0x130); // Updated
	BUILD_ACCESS(this, C_FontRepository**, fontRepository, 0xEC8); // Updated
	BUILD_ACCESS(this, C_Font*, mcFont, 0xED8); // Updated

	C_Font* getTheGoodFontThankYou() {
		return (*fontRepository)->fontList->fontEntries[7].font;
	};

	C_Font* getTheRandomFontPlease() {
		return (*fontRepository)->fontList->fontEntries[4].font;
	};

	C_Font* getOldFont() {
		return (*fontRepository)->fontList->fontEntries[7].font;
	};

	C_Font* getTheBetterFontYes() {
		return (*fontRepository)->fontList->fontEntries[3].font;
	}

	C_Font* getMCFont() {
		return mcFont;
	}

	const bool canUseKeybinds() {
		return canUseKeys;
	};

	__int64 getServerEntries();
};

class C_GuiData {
private:
	char pad_0x0000[0x30]; //0x0000 // Updated
public: 
	union {
		struct {
			float widthReal; //0x0018 
			float heightReal; //0x001C 
		};
		vec2_t windowSizeReal; //0x0018
	};

	float widthReal2; //0x0020 
	float heightReal2; //0x0024 
	union {
		struct {
			float widthGame; //0x0028 
			float heightGame; //0x002C 
		};
		vec2_t windowSize;  //0x0028 
	};


	void displayClientMessageVA(const char* fmt, va_list lis) {
		char message[300];
		int numCharacters = vsprintf_s(message, 300, fmt, lis);
		displayClientMessage(&std::string(message));
	}

	void displayClientMessageF(const char* fmt, ...) {
		va_list arg;
		va_start(arg, fmt);
		displayClientMessageVA(fmt, arg);
		va_end(arg);
	}
	void displayClientMessage(std::string* a2) { // Updated
		using displayClientMessage = void(__thiscall*)(void*, TextHolder); // This signature actually exists 2 times but we got luck that our function is the first in memory
		static displayClientMessage displayMessageFunc = reinterpret_cast<displayClientMessage>(Utils::FindSignature("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 0F B6 E0 4C 8B F9"));

		TextHolder text = TextHolder(*a2);

		displayMessageFunc(this, text);
	};
};

struct PtrToGameSettings3
{
private:
	char pad_0x0000[0x18]; //0x0000
public:
	C_GameSettingsInput* settingsInput;
};

struct PtrToGameSettings2
{
private:
	char pad_0x0000[0x148]; //0x0000
public:
	PtrToGameSettings3* ptr;
};

struct PtrToGameSettings1
{
private:
	char pad_0x0000[0x20]; //0x0000 // Updated
public:
	PtrToGameSettings2* ptr;
};

class C_ClientInstance {
private:
	char pad_0x0[0xC8];  // 0x0 // Updated
public:
	MinecraftGame* minecraftGame;  // 0xC8 // Updated
	Minecraft* minecraft;          // 0xD0 // Updated
private:
	char pad_0xD8[0x8];  // 0xD8 // Updated
public:
	LevelRenderer* levelRenderer;  // 0xE0 // Updated
private:
	char pad_0xE8[0x8];  // 0xE8 // Updated
public:
	C_LoopbackPacketSender* loopbackPacketSender;  // 0xF0 // Updated
private:
	char pad_0xF8[0x18];  // 0xF8 // Updated
public:
	PtrToGameSettings1* ptr;  // 0x110 // Updated
private:
	char pad_0x118[0x8];  // 0x118 // Updated
public:
	HitDetectSystem* hitDetectSystem;  // 0x120 // Updated
private:
	char pad_0x128[0x3D8];  // 0x128 // Updated
public:
	class ItemInHandRenderer* itemInHandRenderer;  // 0x500 // Updated

	C_LocalPlayer* getLocalPlayer() {
		return Utils::CallVFunc<27, C_LocalPlayer*>(this); // Updated
	};

	PointingStruct* getPointerStruct() {
		return nullptr;
	}

	void grabMouse() {
		return Utils::CallVFunc<304, void>(this);
	}

	void releaseMouse() {
		return Utils::CallVFunc<305, void>(this);
	}

	glmatrixf* getRefDef() {
		uintptr_t _this = reinterpret_cast<uintptr_t>(this);
		//logF("refderf %llX", _this + 0x258);
		return reinterpret_cast<glmatrixf*>(_this + 0x300); // Updated
	};

	vec2_t* getMousePos() {
		uintptr_t _this = reinterpret_cast<uintptr_t>(this);
		return reinterpret_cast<vec2_t*>(_this + 0x468); // Updated
	}

	C_GuiData* getGuiData() {
		return (C_GuiData*)*reinterpret_cast<__int64*>(reinterpret_cast<C_GuiData*>(reinterpret_cast<__int64>(this) + 0x510));
	};

	vec2_t getFov() {
		uintptr_t _this = reinterpret_cast<uintptr_t>(this);
		vec2_t fov;
		fov.x = *reinterpret_cast<float*>(_this + 0x6A0); // Updated
		fov.y = *reinterpret_cast<float*>(_this + 0x6B4); // Updated
		return fov;
	}

	C_Font* _getFont() { // Updated
		using getFont_t = C_Font * (__fastcall*)(C_ClientInstance*);
		static getFont_t getFontFunc = reinterpret_cast<getFont_t>(Utils::FindSignature("48 89 5C 24 ? 57 48 83 EC 30 48 8B DA 48 8B 89 ? ? ? ? 48 8B 01 48 8D 54 24 ? 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 90 48 8B 10 48 85 D2 74 65 48 8B 48 08 48 85 C9 74 0B F0 FF 41 08 48 8B 10 48 8B 48 08 48 8B 3A 48 85 C9 74 05 E8 ? ? ? ? 48 8B D7 48 8B CB E8 ? ? ? ? 90 33 C0 48 89 44 24 ? 48 8B 4C 24 ? 48 89 44 24 ? 48 85 C9 74 14 E8 ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 05 E8 ? ? ? ? 48 8B C3 48 8B 5C 24 ? 48 83 C4 30 5F C3 E8 ? ? ? ? 90 CC CC CC 48 83 EC 28"));
		return getFontFunc(this);
	}

	C_Font* _getRuneFont() { // Updated
		using getRuneFont_t = C_Font * (__fastcall*)(C_ClientInstance*);
		static getRuneFont_t getRuneFontFunc = reinterpret_cast<getRuneFont_t>(Utils::FindSignature("48 89 5C 24 ? 57 48 83 EC 30 48 8B DA 48 8B 89 ? ? ? ? 48 8B 01 48 8D 54 24 ? 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 90 48 8B 10 48 85 D2 74 65 48 8B 48 08 48 85 C9 74 0B F0 FF 41 08 48 8B 10 48 8B 48 08 48 8B 3A 48 85 C9 74 05 E8 ? ? ? ? 48 8B D7 48 8B CB E8 ? ? ? ? 90 33 C0 48 89 44 24 ? 48 8B 4C 24 ? 48 89 44 24 ? 48 85 C9 74 14 E8 ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 05 E8 ? ? ? ? 48 8B C3 48 8B 5C 24 ? 48 83 C4 30 5F C3 E8 ? ? ? ? 90 CC CC CC 48 89 5C 24"));
		return getRuneFontFunc(this);
	}

	C_Font* _getUnicodeFont() { // Updated
		using getUnicodeFont_t = C_Font * (__fastcall*)(C_ClientInstance*);
		static getUnicodeFont_t getUnicodeFontFunc = reinterpret_cast<getUnicodeFont_t>(Utils::FindSignature("48 89 5C 24 ? 57 48 83 EC 30 48 8B DA 48 8B 89 ? ? ? ? 48 8B 01 48 8D 54 24 ? 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 90 48 8B 10 48 85 D2 74 65 48 8B 48 08 48 85 C9 74 0B F0 FF 41 08 48 8B 10 48 8B 48 08 48 8B 3A 48 85 C9 74 05 E8 ? ? ? ? 48 8B D7 48 8B CB E8 ? ? ? ? 90 33 C0 48 89 44 24 ? 48 8B 4C 24 ? 48 89 44 24 ? 48 85 C9 74 14 E8 ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 05 E8 ? ? ? ? 48 8B C3 48 8B 5C 24 ? 48 83 C4 30 5F C3 E8 ? ? ? ? 90 CC CC CC 40 53"));
		return getUnicodeFontFunc(this);
	}

	inline C_GameSettingsInput* getGameSettingsInput() { return this->ptr->ptr->ptr->settingsInput; };
};
