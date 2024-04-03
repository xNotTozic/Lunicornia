#pragma once
#include "../Utils/HMath.h"
#include "CInventory.h"

class C_InventoryAction // Updated
{
public:
	C_InventoryAction() = default;
	C_InventoryAction(int slot, C_ItemStack* sourceItem, C_ItemStack* targetItem, int sourceType = 0,int type = 0)
	{
		memset(this, 0x0, sizeof(C_InventoryAction));
		this->slot = slot;
		if(sourceItem != nullptr)
			this->sourceItem = *sourceItem;
		if(targetItem != nullptr)
			this->targetItem = *targetItem;
		this->inventorySource = sourceType;
		//this->type = type;
	}
public:
	int inventorySource; // Updated
	int slot;                             //0xC // Updated
	int sourceItemDescriptor;  //0x10 // Updated
	int targetItemDescriptor;  //0x90 // Updated
	C_ItemStack sourceItem;  //0x110 // Updated
	C_ItemStack targetItem;  //0x1A0 // Updated
};

class C_InventoryTransaction {
private:
	char pad_0x0[0x58];//0x0
};

class C_InventoryTransactionManager
{
public:
	uintptr_t* player; //0x0 // Updated
	C_InventoryTransaction transac; //0x8 // Updated
private:
	int unknown; //0x60 // Updated
	// Total size: 0x68 // Updated
public:
	void addInventoryAction(C_InventoryAction const& action) // Updated
	{
		using InventoryTransactionManager__addAction_t = void(__fastcall*)(C_InventoryTransactionManager*, C_InventoryAction const&);
		static InventoryTransactionManager__addAction_t InventoryTransactionManager__addAction = reinterpret_cast<InventoryTransactionManager__addAction_t>(Utils::FindSignature("48 89 5C ? ? 55 56 57 41 56 41 57 48 83 EC ? 45 0F B6 ? 4C 8B F2 48 8B F9"));
		if (InventoryTransactionManager__addAction != 0)
			InventoryTransactionManager__addAction(this, action);
	}
};


