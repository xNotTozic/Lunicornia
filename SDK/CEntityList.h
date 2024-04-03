#pragma once

#include "../Utils/HMath.h"
class C_Entity;

class C_EntityList
{
public:
private:
	char pad_0x0000[0x70]; //0x0000 // Updated
public:
	uintptr_t firstEntity; //0x0050  // Updated
	uintptr_t lastEntity; //0x0058  // Updated
	uintptr_t endAddr; //0x0060  // Updated

	inline size_t getListSize() {
		return (lastEntity - firstEntity) / sizeof(uintptr_t);
	}

	inline C_Entity* get(std::size_t idx) {
		if (idx >= getListSize())
			return 0;
		return *reinterpret_cast<C_Entity**>(firstEntity + (idx * sizeof(uintptr_t)));
	}

	C_Entity* operator[](std::size_t idx) { 
		return get(idx);
	}
}; //Size=0x0050


class C_MobEntityList // Updated
{
public:
private:
	char pad_0x0000[0x38]; //0x0000  // Updated
public: 
	uintptr_t firstEntity; //0x0038  // Updated
	uintptr_t lastEntity; //0x0040  // Updated
	uintptr_t endAddr; //0x0048  // Updated

	inline size_t getListSize() {
		return (lastEntity - firstEntity) / sizeof(uintptr_t);
	}

	inline C_Entity* get(std::size_t idx) {
		if (idx >= getListSize())
			return 0;
		return *reinterpret_cast<C_Entity**>(firstEntity + (idx * sizeof(uintptr_t)));
	}

	C_Entity* operator[](std::size_t idx) {
		return get(idx);
	}
}; //Size=0x0050