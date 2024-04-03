#pragma once

#include "../Utils/HMath.h"
#include "../Utils/Utils.h"
#include "TextHolder.h"
#include "CEntityList.h"
#include "CBlockLegacy.h"
#include "CInventory.h"
#include "CInventoryTransaction.h"
#include "ActorFlags.h"
class Dimension;

class C_GameMode;

class PointingStruct
{
private:
	char pad_0x0000[0x850]; //0x0000
public:
	int rayHitType; //0x0850
	int blockSide; //0x0854
	vec3_ti block; //0x0858
	vec3_t rayHitVec; //0x0864
	C_Entity* entityPtr; //0x0870
};

class C_Player;

class C_Entity // Updated VTables Fuck the offsets ain't updating them
{
public:
	uintptr_t* ptrToPtrToEntList; //0x0008
private:
	char pad_0010[0xE0]; //0x0010
public:
	union {
		struct {
			float pitch; //0x00F0
			float yaw; //0x00F4
		};
		vec2_t viewAngles;
	};
	float pitch2; //0x00F8
	float yaw2; //0x00FC
private:
	char pad_0100[0x10]; //0x0100
public:
	vec3_t eyePos0; //0x0110
private:
	char pad_0x11C[0x5C]; //0x11C
public:
	bool onGround; //0x0178
private:
	char pad_0x179[0x1B]; //0x179
public:
	float fallDistance; //0x194
private:
	char pad_0x198[0x7C]; //0x0198
public:
	float spectatorMode; //0x0214
private:
	char pad_0x218[0x8]; //0x218
public:
	float stepHeight; //0x0220
private:
	char pad_0x228[0x14]; //0x224
public:
	float web; //0x0238
private:
	char pad_0x23C[0x1]; //0x023C
public:
	bool didEnterWaterBool; //0x023D
private:
	char pad_023E[0x4E]; //0x023E
public:
	int ticksAlive; //0x028C
private:
	char pad_0290[0xB8]; //0x0290
public:
	C_BlockSource* region; //0x348
private:
	char pad_0x350[0xE0]; //0x350
public:
	AABB aabb; //0x0430
private:
	char pad_0x448[0x4]; //0x0448
public:
	float width; //0x044C
	float height; //0x0450
	vec3_t currentPos; //0x0454
	vec3_t oldPos; //0x0460
	vec3_t velocity; //0x046C
private:
	char pad_0x0478[0x58]; //0x478
public:
	__int64 entityRuntimeId; //0x4D0
private:
	char pad_0478[0x338]; //0x04D8
public:
	float bodyYaw; //0x0810
	float oldBodyYaw; //0x0814
	float yawUnused1; //0x0818
	float yawUnused2; //0x081C
	int damageTime; //0x0820
private:
	char pad_0824[0x88]; //0x0824
public:
	int timeSinceDeath; //0x08AC
private:
	char pad_08B0[0x1E4]; //0x08B0
public:
	bool canFly; //0x0A94
private:
	char pad_0x0A95[0x62B]; //0x0A95
public:
	int16_t itemData; //0x10C0
	int16_t itemId; //0x10C2
private:
	char pad_10CC[0x1FC]; //0x10C4
public:
	C_InventoryTransactionManager transac; //0x12C0
private:
	char pad_0x1324[0xA6C]; //0x1324
public:
	int gamemode; //0x1D94
private:
	char pad_1DA4[0x198]; //0x1D98 
public:
	TextHolder uuid; //0x1F30

public:
	virtual int getStatusFlag(ActorFlags);
	virtual void setStatusFlag(ActorFlags, bool);
	virtual int getLastHurtByEntity(void);
	virtual void setLastHurtByC_Entity(C_Entity*);
	virtual int getLastHurtByPlayer(void);
	virtual void setLastHurtByPlayer(C_Player*);
	virtual int getLastHurtEntity(void);
	virtual void setLastHurtC_Entity(C_Entity*);
	virtual void outOfWorld(void);
	virtual void reloadHardcoded(__int64, __int64 const&);
	virtual void reloadHardcodedClient(__int64, __int64 const&);
	virtual void initializeComponents(__int64, __int64 const&);
	virtual void reloadComponents(__int64, __int64 const&);
	virtual void _serverInitItemStackIds(void);
	virtual void _doInitialMove(void);
	virtual void hasComponent(__int64 const&);

private:
	virtual void Destructor();

public:
	virtual void resetUserPos(bool);
	virtual int getOwnerC_EntityType(void);
	virtual void remove(void);
	virtual bool isRuntimePredictedMovementEnabled(void);
	virtual int getPredictedMovementValues(void);
	virtual vec3_t* getPos(void);
	virtual vec3_t* getPosOld(void);
	virtual float getPosExtrapolated(float);
	virtual float getAttachPos(__int64, float);
	virtual int getFiringPos(void);
	virtual void move(vec3_t const&);
	virtual void move(__int64&, vec3_t const&);
	virtual float getInterpolatedRidingPosition(float);
	virtual float getInterpolatedBodyRot(float);
	virtual float getInterpolatedHeadRot(float);
	virtual float getInterpolatedBodyYaw(float);
	virtual int getYawSpeedInDegreesPerSecond(void);
	virtual float getInterpolatedWalkAnimSpeed(float);
	virtual float getInterpolatedRidingOffset(float, int);
	virtual void resetInterpolated(void);
	virtual void updateC_EntityInside(AABB const&);
	virtual void updateC_EntityInside(void);
	virtual bool isFireImmune(void);
	virtual void breaksFallingBlocks(void);
	virtual void blockedByShield(__int64 const&, C_Entity&);
	virtual void canDisableShield(void);
	virtual void teleportTo(vec3_t const&, bool, int, int, bool);
	virtual void tryTeleportTo(vec3_t const&, bool, bool, int, int);
	virtual void chorusFruitTeleport(vec3_t const&);
	virtual void lerpMotion(vec3_t const&);
	virtual void tryCreateAddEntityPacket(void);
	virtual void normalTick(void);
	virtual void baseTick(void);
	virtual void passengerTick(void);
	virtual void positionPassenger(C_Entity&, float);
	virtual void startRiding(C_Entity&);
	virtual void addPassenger(C_Entity&);
	virtual void flagPassengerToRemove(C_Entity&);
	virtual int getExitTip(std::string const&, __int64, __int64);
	virtual int getEntityLocNameString(void);
	virtual void intersects(vec3_t const&, vec3_t const&);
	virtual bool isInWall(void);
	virtual bool isInvisible(void);
	virtual bool canShowNameTag(void);
	virtual void canExistInPeaceful(void);
	virtual void setNameTagVisible(bool);
	virtual TextHolder* getNameTag(void);
	virtual int getNameTagAsHash(void);
	virtual TextHolder* getFormattedNameTag(void);
	virtual void filterFormattedNameTag(__int64 const&);
	virtual void setNameTag(std::string const&);
	virtual int getAlwaysShowNameTag(void);
	virtual void setScoreTag(std::string const&);
	virtual int getScoreTag(void);
	virtual bool isInWater(void);
	virtual bool isUnderLiquid(__int64);
	virtual bool isOverWater(void);
	virtual void setBlockMovementSlowdownMultiplier(C_BlockLegacy const&, vec3_t const&);
	virtual void resetBlockMovementSlowdownMultiplier(void);
	virtual int getCameraOffset(void);
	virtual int getShadowHeightOffs(void);
	virtual int getShadowRadius(void);
	virtual float getHeadLookVector(float);
	virtual void canSeeInvisible(void);
	virtual bool canSee(vec3_t const&);
	virtual bool canSee(C_Entity const&);
	virtual void canInteractWithOtherEntitiesInGame(void);
	virtual bool isSkyLit(float);
	virtual float getBrightness(float, __int64 const&);
	virtual void interactPreventDefault(void);
	virtual void playerTouch(C_Player&);
	virtual void onAboveBubbleColumn(bool);
	virtual void onInsideBubbleColumn(bool);
	virtual bool isImmobile(void);
	virtual bool isSilent(void);
	virtual bool isSilentObserver(void);
	virtual bool isPickable(void);
	virtual bool isFishable(void);
	virtual bool isSleeping(void);
	virtual void setSleeping(bool);
	virtual bool isShootable(void);
	virtual void setSneaking(bool);
	virtual bool isBlocking(void);
	virtual bool isDamageBlocked(__int64 const&);
	virtual bool isAlive(void);
	virtual bool isOnFire(void);
	virtual bool isOnHotBlock(void);
	virtual bool isCreativeModeAllowed(void);
	virtual bool isSurfaceC_Entity(void);
	virtual bool isTargetable(void);
	virtual bool isLocalPlayer(void);
	virtual bool isRemotePlayer(void);
	virtual bool isPlayer(void);
	virtual bool isAffectedByWaterBottle(void);
	virtual bool canAttack(C_Entity*, bool);
	virtual void setTarget(C_Entity*);
	virtual bool isValidTarget(C_Entity*);
	virtual void attack(C_Entity&, __int64 const&);
	virtual void performRangedAttack(C_Entity&, float);
	virtual int getEquipmentCount(void);
	virtual void setOwner(uint64_t);
	virtual void setSitting(bool);
	virtual void onTame(void);
	virtual void onFailedTame(void);
	virtual int getInventorySize(void);
	virtual int getEquipSlots(void);
	virtual int getChestSlots(void);
	virtual void setStanding(bool);
	virtual void canPowerJump(void);
	virtual void setCanPowerJump(bool);
	virtual bool isEnchanted(void);
	virtual void vehicleLanded(vec3_t const&, vec3_t const&);
	virtual void shouldRender(void);
	virtual void playAmbientSound(void);
	virtual int getAmbientSound(void);
	virtual bool isInvulnerableTo(__int64 const&);
	virtual int getBlockDamageCause(C_Block const&);
	virtual void animateHurt(void);
	virtual void doFireHurt(int);
	virtual void onLightningHit(void);
	virtual void onBounceStarted(vec3_ti const&, C_Block const&);
	virtual void feed(int);
	virtual void handleC_EntityEvent(__int64, int);
	virtual int getPickRadius(void);
	virtual int getC_EntityRendererId(void);
	virtual void spawnAtLocation(int, int);
	virtual void spawnAtLocation(int, int, float);
	virtual void spawnAtLocation(C_ItemStack const&, float);
	virtual void despawn(void);
	virtual void killed(C_Entity&);
	virtual void awardKillScore(C_Entity&, int);
	virtual void setArmor(int, C_ItemStack const&);
	virtual C_ItemStack* getArmor(int);
	virtual int getAllArmor(void);
	virtual int getArmorMaterialTypeInSlot(int);
	virtual int getArmorMaterialTextureTypeInSlot(int);
	virtual int getArmorColorInSlot(int, int);
	virtual int getEquippedSlot(int);
	virtual void setEquippedSlot(int, C_ItemStack const&);
	virtual void setCarriedItem(C_ItemStack const*);
	virtual int getCarriedItem(void);
	virtual void setOffhandSlot(C_ItemStack const*);
	virtual C_ItemStack* getEquippedTotem(void);
	virtual void consumeTotem(void);
	virtual void save(__int64*);
	virtual void saveWithoutId(__int64&);
	virtual void load(__int64 const&, __int64&);
	virtual void loadLinks(__int64 const&, std::vector<__int64>&, __int64&);
	virtual int getC_EntityTypeId(void);
	virtual void queryC_EntityRenderer(void);
	virtual int getSourceUniqueID(void);
	virtual void thawFreezeEffect(void);
	virtual void canFreeze(void);
	virtual bool isWearingLeatherArmor(void);
	virtual int getLiquidAABB(__int64);
	virtual void handleInsidePortal(vec3_ti const&);
	virtual int getPortalCooldown(void);
	virtual int getPortalWaitTime(void);
	virtual void canChangeDimensionsUsingPortal(void);
	virtual void changeDimension(Dimension*, int);
	virtual void changeDimension(__int64 const&);
	virtual int getControllingPlayer(void);
	virtual void checkFallDamage(float, bool);
	virtual void causeFallDamage(float, float, __int64);
	virtual void handleFallDistanceOnServer(float, float, bool);
	virtual void playSynchronizedSound(__int64, vec3_t const&, C_Block const&, bool);
	virtual void playSynchronizedSound(__int64, vec3_t const&, int, bool);
	virtual void onSynchedFlagUpdate(int, long, long);
	virtual void onSynchedDataUpdate(int);
	virtual void canAddPassenger(C_Entity&);
	virtual void canPickupItem(C_ItemStack const&);
	virtual void canBePulledIntoVehicle(void);
	virtual void inCaravan(void);
	virtual bool isLeashableType(void);
	virtual void tickLeash(void);
	virtual void sendMotionPacketIfNeeded(void);
	virtual void canSynchronizeNewC_Entity(void);
	virtual void stopRiding(bool, bool, bool);
	virtual void startSwimming(void);
	virtual void stopSwimming(void);
	virtual void buildDebugInfo(std::string&);
	virtual int getCommandPermissionLevel(void);
	virtual bool isClientSide(void);
	virtual class AttributeInstance* getMutableAttribute(class Attribute* Attribute);
	virtual class AttributeInstance* getAttribute(class Attribute* Attribute);
	virtual int getDeathTime(void);
	virtual void heal(int);
	virtual bool isInvertedHealAndHarm(void);
	virtual void canBeAffected(int);
	virtual void canBeAffectedByArrow();
	virtual void onEffectAdded();
	virtual void onEffectUpdated();
	virtual void onEffectRemoved();
	virtual void canObstructSpawningAndBlockPlacement(void);
	virtual class AnimationComponent* getAnimationComponent(void);
	virtual void openContainerComponent(C_Player&);
	virtual void swing(void);
	virtual void useItem(C_ItemStack&, __int64, bool);
	virtual void hasOutputSignal(char);
	virtual int getOutputSignal(void);
	virtual int getDebugText(std::vector<std::string>&);
	virtual int getMapDecorationRotation(void);
	virtual int getPassengerYRotation(C_Entity const&);
	virtual void add(C_ItemStack&);
	virtual void drop(C_ItemStack const&, bool);
	virtual int getInteraction(C_Player&, __int64&, vec3_t const&);
	virtual void canDestroyBlock(C_Block const&);
	virtual void setAuxValue(int);
	virtual void setSize(float, float);
	virtual void onOrphan(void);
	virtual void wobble(void);
	virtual void wasHurt(void);
	virtual void startSpinAttack(void);
	virtual void stopSpinAttack(void);
	virtual void setDamageNearbyC_Entitys(bool);
	virtual void renderDebugServerState(__int64 const&);
	virtual void reloadLootTable(void);
	virtual void reloadLootTable(__int64 const&);
	virtual int getDeletionDelayTimeSeconds(void);
	virtual void kill(void);
	virtual void die(__int64 const&);
	virtual void shouldDropDeathLoot(void);
	virtual void shouldTick(void);
	virtual void applySnapshot(__int64 const&, __int64 const&);
	virtual float getNextStep(float);
	virtual int getLootTable(void);
	virtual void onPush(C_Entity&);
	virtual vec3_ti getLastDeathPos(void);
	virtual int getLastDeathDimension(void);
	virtual void hasDiedBefore(void);
	virtual void doWaterSplashEffect(void);
	virtual void _shouldProvideFeedbackOnHandContainerItemSet(int, C_ItemStack const&);
	virtual void _shouldProvideFeedbackOnArmorSet(int, C_ItemStack const&);
	virtual void updateC_EntitySpecificMolangVariables(__int64&);
	virtual void shouldTryMakeStepSound(void);
	virtual void canMakeStepSound(void);
	virtual void _hurt(__int64 const&, float, bool, bool);
	virtual void markHurt(void);
	virtual void _getAnimationComponent(__int64&, __int64);
	virtual void readAdditionalSaveData(__int64 const&, __int64&);
	virtual void addAdditionalSaveData(__int64&);
	virtual void _playStepSound(vec3_ti const&, C_Block const&);
	virtual void _playFlySound(vec3_ti const&, C_Block const&);
	virtual void _makeFlySound(void);
	virtual void checkInsideBlocks(float);
	virtual void pushOutOfBlocks(vec3_t const&);
	virtual void spawnTrailBubbles(void);
	virtual void updateInsideBlock(void);
	virtual void _removePassenger(uint64_t const&, bool, bool, bool);
	virtual void _onSizeUpdated(void);
	virtual void _doAutoAttackOnTouch(C_Entity&);
	virtual void knockback(C_Entity*, int, float, float, float, float, float);
	virtual void spawnAnim(void);
	virtual void setSprinting(bool);
	virtual int getHurtSound(void);
	virtual int getDeathSound(void);
	virtual __int64 getSpeed(void);
	virtual void setSpeed(float);
	virtual void hurtEffects(__int64 const&, float, bool, bool);
	virtual int getMeleeWeaponDamageBonus(C_Entity);
	virtual int getMeleeKnockbackBonus(void);
	virtual void travel(float, float, float, bool);
	virtual void applyFinalFriction(float, bool);
	virtual void aiStep(void);
	virtual void aiStep(__int64&);
	virtual void pushC_Entitys(void);
	virtual void lookAt(C_Entity*, float, float);
	virtual bool isLookingAtAnC_Entity(void);
	virtual void checkSpawnRules(bool);
	virtual void checkSpawnObstruction(void);
	virtual float getAttackAnim(float);
	virtual int getItemUseDuration(void);
	virtual int getItemUseStartupProgress(void);
	virtual int getItemUseIntervalProgress(void);
	virtual int getItemUseIntervalAxis(void);
	virtual int getTimeAlongSwing(void);
	virtual void ate(void);
	virtual int getMaxHeadXRot(void);
	virtual bool isAlliedTo(C_Entity*);
	virtual void doHurtTarget(C_Entity*, __int64 const&);
	virtual void canBeControlledByPassenger(void);
	virtual void leaveCaravan(void);
	virtual void joinCaravan(C_Entity);
	virtual void hasCaravanTail(void);
	virtual int getCaravanHead(void);
	virtual int getArmorValue(void);
	virtual int getArmorCoverPercentage(void);
	virtual int getToughnessValue(void);
	virtual void hurtArmorSlots(__int64 const&, int, __int64);
	virtual void setDamagedArmor(int, C_ItemStack const&);
	virtual void sendArmorDamage(__int64);
	virtual void sendArmor(__int64);
	virtual void containerChanged(int);
	virtual void updateEquipment(void);
	virtual void clearEquipment(void);
	virtual int getAllArmorID(void);
	virtual int getAllHand(void);
	virtual int getAllEquipment(void);
	virtual int getArmorTypeHash(void);
	virtual void dropEquipmentOnDeath(__int64 const&, int);
	virtual void dropEquipmentOnDeath(void);
	virtual void clearVanishEnchantedItemsOnDeath(void);
	virtual void sendInventory(bool shouldSelectSlot);
	virtual float getDamageAfterEnchantReduction(__int64 const&, float);
	virtual float getDamageAfterArmorReduction(__int64 const&, float);
	virtual float getDamageAfterResistanceEffect(__int64 const&, float);
	virtual void createAIGoals(void);
	virtual void onBorn(C_Entity&, C_Entity&);
	virtual void setItemSlot(int, C_ItemStack const&);
	virtual void setTransitioningSitting(bool);
	virtual void attackAnimation(C_Entity*, float);
	virtual int getAttackTime(void);
	virtual void _getWalkTargetValue(vec3_ti const&);
	virtual void canExistWhenDisallowC_Entity(void);
	virtual void ascendLadder(void);
	virtual void ascendBlockByJumping(void);
	virtual void descendBlockByCrouching(void);
	virtual void dropContainer(void);
	virtual void initBodyControl(void);
	virtual void jumpFromGround(C_BlockSource const&);
	virtual void jumpFromGround(__int64&, C_BlockSource const&);
	virtual void newServerAiStep(void);
	virtual void _serverAiC_EntityStep(void);
	virtual void dropBags(void);
	virtual void tickDeath(void);
	virtual void updateGliding(void);
	virtual void _allowAscendingScaffolding(void);
	virtual void _getAdjustedAABBForSpawnCheck(AABB const&, vec3_t const&);
public:
	C_InventoryTransactionManager* getTransactionManager() { // Updated
		return reinterpret_cast<C_InventoryTransactionManager*>(reinterpret_cast<__int64>(this) + 0xEC8);
	}

	AABB* getAABB() {
		return &this->aabb;
	}
};

class C_ServerPlayer;

class C_Player : public C_Entity {
public:
	C_PlayerInventoryProxy* getSupplies() { // Updated
		return *reinterpret_cast<C_PlayerInventoryProxy**>(reinterpret_cast<__int64>(this) + 0x848);
	};
public:
	virtual void prepareRegion(__int64&);
	virtual void destroyRegion(void);
	virtual void suspendRegion(void);
	virtual void resendAllChunks(void);
	virtual void _fireWillChangeDimension(void);
	virtual void _fireDimensionChanged(void);
	virtual void changeDimensionWithCredits(Dimension, int);
	virtual void tickWorld(__int64 const&);

private:
	virtual void TryroFunc354();

public:
	virtual int getTickingOffsets(void);
	virtual void moveView(void);
	virtual void moveSpawnView(vec3_t const&, Dimension, int);
	virtual void setName(std::string const&);
	virtual int getTravelledMethod(void);
	virtual void checkMovementStats(vec3_t const&);
	virtual int getCurrentStructureFeature(void);
	virtual bool isAutoJumpEnabled(void);
	virtual void respawn(void);
	virtual void resetRot(void);
	virtual bool isInTrialMode(void);
	virtual void hasResource(int);
	virtual void completeUsingItem(void);
	virtual void startDestroying(void);
	virtual void stopDestroying(void);
	virtual void openPortfolio(void);
	virtual void openBook(int, bool, int, __int64);
	virtual void openTrading(uint64_t const&, bool);
	virtual bool canOpenContainerScreen(void);
	virtual void openChalkboard(__int64&, bool);
	virtual void openNpcInteractScreen(std::shared_ptr<__int64>);
	virtual void openInventory(void);
	virtual void displayChatMessage(std::string const&, std::string const&);
	virtual void displayClientMessage(TextHolder*);
	virtual void displayTextObjectMessage(__int64 const&, std::string const&, std::string const&);
	virtual void displayTextObjectWhisperMessage(__int64 const&, std::string const&, std::string const&);
	virtual void displayTextObjectWhisperMessage(std::string const&, std::string const&, std::string const&);
	virtual void displayWhisperMessage(std::string const&, std::string const&, std::string const&, std::string const&);
	virtual void startSleepInBed(vec3_ti const&);
	virtual void stopSleepInBed(bool, bool);
	virtual void canStartSleepInBed(void);
	virtual int getSleepTimer(void);
	virtual int getPreviousTickSleepTimer(void);
	virtual void openSign(vec3_ti const&, bool);
	virtual void playEmote(std::string const&, bool);
	virtual bool isHostingPlayer(void);
	virtual bool isLoading(void);
	virtual bool isPlayerInitialized(void);
	virtual void stopLoading(void);
	virtual void registerTrackedBoss(uint64_t);
	virtual void unRegisterTrackedBoss(uint64_t);
	virtual void setPlayerGameType(int GameType);
	virtual void initHUDContainerManager(void);
	virtual void _crit(C_Entity&);
	virtual __int64* getEventing(void);
	virtual int getUserId(void);
	virtual void sendEventPacket(__int64&);
	virtual void addExperience(int);
	virtual void addLevels(int);

private:
	virtual void TryroFunc404();
	virtual void TryroFunc405();

public:
	virtual void inventoryChanged(__int64&, int, C_ItemStack const&, C_ItemStack const&, bool);

private:
	virtual void TryroFunc407();

public:
	virtual void deleteContainerManager(void);
	virtual bool isEntityRelevant(C_Entity const&);

private:
	virtual void TryroFunc410();

public:
	virtual void onSuspension(void);
	virtual void onLinkedSlotsChanged(void);
	virtual void startCooldown(Item const*, bool);
	virtual int getItemCooldownLeft(__int64 const&);
	virtual int getItemCooldownLeft(long);
	virtual int getMaxItemCooldownLeft(void);
	virtual bool isItemOnCooldown(__int64 const&);

private:
	virtual void TryroFunc418();
	virtual void TryroFunc419();

public:
	virtual void sendNetworkPacket(class Packet&);

private:
	virtual void TryroFunc421();

public:
	virtual void reportMovementTelemetry(__int64);
	virtual bool isSimulated(void);
	virtual int getXuid(void);
	virtual int getMovementSettings(void);
	virtual void addSavedChunk(__int64 const&);
	virtual int getMaxChunkBuildRadius(void);
	virtual void onMovePlayerPacketNormal(vec3_t const&, vec2_t const&, float);
	virtual void _createChunkSource(__int64&);
	virtual void setAbilities(__int64 const&);
};

class C_ServerPlayer : public C_Player {
public:
	void sendInventory() {
		
		//Utils::CallVFunc<315, void>(this);
	}
};

class C_LocalPlayer : public C_Player {
public:
	void sendInventory() {
		//using sendInventory_t = void(__fastcall*)(C_Player*, bool);
		//static sendInventory_t sendInventory = reinterpret_cast<sendInventory_t>(Utils::FindSignature("48 8B C4 55 48 8D A8 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 C7 44 24 ?? FE FF FF FF 48 89 58 ?? 48 89 70 ?? 48 89 78 ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 0F B6 DA 48 8B F1"));
		//sendInventory(this, true);
	};

	// Updated
	void unlockAchievments() { // MinecraftEventing::fireEventAwardAchievement
		using fireEventAward = void(__fastcall*)(void*, int);
		static fireEventAward fireEventAwardFunc = reinterpret_cast<fireEventAward>(Utils::FindSignature("48 85 C9 0F 84 ? ? ? ? 48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B 01"));
		for (int i = 0; i < 100; i++)
			fireEventAwardFunc(this, i);
	}

	void swingArm() {
		//using SwingArm = void(__thiscall*)(void*);
		//static SwingArm swingFunc = reinterpret_cast<SwingArm>(Utils::FindSignature("40 57 48 83 EC ?? 48 C7 44 24 ?? FE FF FF FF 48 89 5C 24 ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 44 24 ?? 48 8B D9 80 B9"));
		//swingFunc(this);
		this->swing();
	}
	/*void localPlayerTurn(vec2_t* viewAngles) {
		using Turn = void(__thiscall*)(void*, vec2_t*);
		static Turn TurnFunc = reinterpret_cast<Turn>(Utils::FindSignature("4C 8B DC 55 57 ?? ?? ?? ?? ?? ?? ?? 48 ?? ?? ?? ?? ?? ?? 45 ?? ?? ?? ?? ?? ?? ?? 48 8B 05 D6 D4 A5 01 48 33 C4 48 89 45 ?? 49 89 5B ?? 48 8B F9 ?? ?? ?? ?? ?? ?? ?? 48 8B DA 4D 89 73 E8 41 0F 29 73 D8 41 0F 29 7B C8 48 8B 01 FF 90 ?? ?? ?? ?? F2 0F 10 03"));
		TurnFunc(this, viewAngles);
	}*/
	void applyTurnDelta(vec2_t* viewAngleDelta) // Updated
	{
		using applyTurnDelta = void(__thiscall*)(void*, vec2_t*);
		static applyTurnDelta TurnDelta = reinterpret_cast<applyTurnDelta>(Utils::FindSignature("48 8B C4 48 89 58 18 48 89 68 20 56 57 41 56 48 81 EC ?? ?? ?? ?? 0F 29 70 D8 0F 29 78 C8 44 0F 29 40 ?? 48 8B 05 ?? ?? ?? ??"));
		TurnDelta(this, viewAngleDelta);
	}
	void setGameModeType(int gma)
	{
		// Player::setPlayerGameType
		using setGameMode = void(__thiscall*)(void*, int);
		static setGameMode Game_Mode = reinterpret_cast<setGameMode>(Utils::FindSignature("40 57 48 83 EC ?? 48 C7 44 24 ?? FE FF FF FF 48 89 5C 24 ?? 48 89 ?? 24 ?? 48 89 ?? 24 ?? 8B FA 48 8B D9 8B B1"));
		Game_Mode(this, gma);
	}
};

#define Player C_Player*
#define Entity C_Entity*
