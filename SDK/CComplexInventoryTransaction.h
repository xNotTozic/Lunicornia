#pragma once
#include "../Utils/HMath.h"
#include "CInventory.h"
#include "CInventoryTransaction.h"

class C_ComplexInventoryTransaction {
public:
	C_ComplexInventoryTransaction()
	{
		memset(this, 0, sizeof(C_ComplexInventoryTransaction));
	}
	C_ComplexInventoryTransaction(C_InventoryTransaction& transac)
	{
		static uintptr_t** ComplexInventoryTransactionVtable = 0x0;
		if (ComplexInventoryTransactionVtable == 0x0) {
			uintptr_t sigOffset = Utils::FindSignature("4C 8D 3D ? ? ? ? 4C 89 7D ? E8 ? ? ? ? 48 89 45 ? 89 75"); // Updated
			int offset = *reinterpret_cast<int*>(sigOffset + 3);
			ComplexInventoryTransactionVtable = reinterpret_cast<uintptr_t * *>(sigOffset + offset + /*length of instruction*/ 7);
			if (ComplexInventoryTransactionVtable == 0x0 || sigOffset == 0x0)
				logF("C_ComplexInventoryTransactionVtable signature not working!!!");
		}
		memset(this, 0, sizeof(C_ComplexInventoryTransaction)); // Avoid overwriting vtable
		vTable = ComplexInventoryTransactionVtable;
		uintptr_t boi = reinterpret_cast<uintptr_t>(this);
		using constructor_t = void(__fastcall*)(uintptr_t,C_InventoryTransaction&);
		static constructor_t constructor = reinterpret_cast<constructor_t>(Utils::FindSignature("48 89 5C ? ? 89 54 24 ? 55 56 57 41 56 41 57 48 8B EC")); // Updated
		if (constructor != 0)
			constructor(boi+0x10,transac);
		this->actionType = 0;
	}
	uintptr_t** vTable; //0x0000
	int actionType;//0x8
	int unknown;//0xC
	C_InventoryTransaction transac;//0x10
};

class C_ItemUseInventoryTransaction : public C_ComplexInventoryTransaction
{
public:
	C_ItemUseInventoryTransaction()
	{
		memset(this,0x0, sizeof(C_ItemUseInventoryTransaction));
		using ItemUseInventoryTransactionContructor = void(__fastcall*)(C_ItemUseInventoryTransaction*);
		static ItemUseInventoryTransactionContructor constructor = reinterpret_cast<ItemUseInventoryTransactionContructor>(Utils::FindSignature("48 8D 05 ? ? ? ? 48 89 07 48 8D 8F ? ? ? ? 48 8D 96 ? ? ? ? E8 ? ? ? ? 48 8B 86")); // Updated
		if (constructor != 0)
			constructor(this);
	}
	C_ItemUseInventoryTransaction(int slot,C_ItemStack const* item,vec3_t const pos,int blockSide = 255,int runtimeBlockId = 0)
	{
		memset(this, 0x0, sizeof(C_ItemUseInventoryTransaction));
		using ItemUseInventoryTransactionContructor = void(__fastcall*)(C_ItemUseInventoryTransaction*);
		static ItemUseInventoryTransactionContructor constructor = reinterpret_cast<ItemUseInventoryTransactionContructor>(Utils::FindSignature("48 8D 05 ? ? ? ? 48 89 07 48 8D 8F ? ? ? ? 48 8D 96 ? ? ? ? E8 ? ? ? ? 48 8B 86")); // Updated
		if (constructor != 0)
			constructor(this);
		this->slot = slot;
		this->item = *item;
		this->pos = pos;
		this->runtimeBlockId = runtimeBlockId;
		this->blockSide = blockSide;
	}
private:
	char pad_0x68[0x4];//0x68
public:
	vec3_ti blockPos;//0x6C
	int runtimeBlockId;//0x78
	int blockSide;//0x7C
	int slot;//0x80
private:
	char pad_0x84[0x4];//0x84
public:
	C_ItemStack item;//0x88
	vec3_t pos;//0x110
	vec3_t clickPos;//0x11C
};

class C_ItemReleaseInventoryTransaction : public C_ComplexInventoryTransaction
{
public:
	C_ItemReleaseInventoryTransaction()
	{
		memset(this, 0x0, sizeof(C_ItemReleaseInventoryTransaction));
		using ItemReleaseInventoryTransactionContructor = void(__fastcall*)(C_ItemReleaseInventoryTransaction*);
		static ItemReleaseInventoryTransactionContructor constructor = reinterpret_cast<ItemReleaseInventoryTransactionContructor>(Utils::FindSignature("48 8D 05 ? ? ? ? 48 8B F1 48 89 01 8B FA 48 83 C1 ? E8 ? ? ? ? 48 8D 4E ? E8 ? ? ? ? 48 8D 05 ? ? ? ? 48 89 06 40 F6 C7 ? 74 0D BA ? ? ? ? 48 8B CE E8 ? ? ? ? 48 8B 5C ? ? 48 8B C6 48 8B 74 ? ? 48 83 C4 ? 5F C3 48 89 5C ? ? 57")); // Updated
		if (constructor != 0)
			constructor(this);
	}
	C_ItemReleaseInventoryTransaction(int slot,C_ItemStack const* item ,vec3_t const pos)
	{
		memset(this, 0x0, sizeof(C_ItemReleaseInventoryTransaction));
		using ItemReleaseInventoryTransactionContructor = void(__fastcall*)(C_ItemReleaseInventoryTransaction*);
		static ItemReleaseInventoryTransactionContructor constructor = reinterpret_cast<ItemReleaseInventoryTransactionContructor>(Utils::FindSignature("48 8D 05 ? ? ? ? 48 8B F1 48 89 01 8B FA 48 83 C1 ? E8 ? ? ? ? 48 8D 4E ? E8 ? ? ? ? 48 8D 05 ? ? ? ? 48 89 06 40 F6 C7 ? 74 0D BA ? ? ? ? 48 8B CE E8 ? ? ? ? 48 8B 5C ? ? 48 8B C6 48 8B 74 ? ? 48 83 C4 ? 5F C3 48 89 5C ? ? 57")); // Updated
		if (constructor != 0)
			constructor(this);
		this->slot = slot;
		this->item = *item;
		this->pos = pos;
	}
private:
	char pad_0x68[0x4];//0x68
public:
	int slot;//0x6C
	C_ItemStack item;//0x70
	vec3_t pos;//0xF8
	int unknown;//0x104
};
