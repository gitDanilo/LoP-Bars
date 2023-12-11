#ifndef UE4SS_SDK_Engine_HPP
#define UE4SS_SDK_Engine_HPP

#include <vector>
#include "Engine_enums.hpp"

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef int int32;

struct FKey
{
    char pad[0x18];
};

struct FVector
{
    float v[3];
};

struct FRotator
{
    float v[3];
};

struct FColor
{
    int rgba;
};

struct FVector2D
{
    float v[2];
};

struct FGuid
{
    char pad[0x10];
};

struct TArray
{
    void* ptr;
    size_t count;
};

struct FHitResult
{
    char pad[0x88];
};

enum class EControllerHand : uint8
{
    Left,
    Right,
    AnyHand,
    Pad,
    ExternalCamera,
    Gun,
    Special_1,
    Special_2,
    Special_3,
    Special_4,
    Special_5,
    Special_6,
    Special_7,
    Special_8,
    Special_9,
    Special_10,
    Special_11,

    ControllerHand_Count,
};

struct FViewTargetTransitionParams
{
    float BlendTime;                                                                  // 0x0000 (size: 0x4)
    uint8 BlendFunction;                              // 0x0004 (size: 0x1)
    float BlendExp;                                                                   // 0x0008 (size: 0x4)
    uint8 bLockOutgoing;                                                              // 0x000C (size: 0x1)

}; // Size: 0x10

struct FUpdateLevelVisibilityLevelInfo
{
    void* PackageName;                                                                // 0x0000 (size: 0x8)
    void* Filename;                                                                   // 0x0008 (size: 0x8)
    uint8 bIsVisible;                                                                 // 0x0010 (size: 0x1)

}; // Size: 0x14

struct FText
{
    char pad[0x18];
};

struct FForceFeedbackParameters
{
    void* Tag;                                                                        // 0x0000 (size: 0x8)
    bool bLooping;                                                                    // 0x0008 (size: 0x1)
    bool bIgnoreTimeDilation;                                                         // 0x0009 (size: 0x1)
    bool bPlayWhilePaused;                                                            // 0x000A (size: 0x1)
};

struct FTransformBase
{
    char pad[0x28];

}; // Size: 0x28

class AActor : public UObject
{
    char PrimaryActorTick[0x30];                                              // 0x0028 (size: 0x30)
    uint8 bNetTemporary;                                                              // 0x0058 (size: 0x1)
    uint8 bNetStartup;                                                                // 0x0058 (size: 0x1)
    uint8 bOnlyRelevantToOwner;                                                       // 0x0058 (size: 0x1)
    uint8 bAlwaysRelevant;                                                            // 0x0058 (size: 0x1)
    uint8 bReplicateMovement;                                                         // 0x0058 (size: 0x1)
    uint8 bHidden;                                                                    // 0x0058 (size: 0x1)
    uint8 bTearOff;                                                                   // 0x0058 (size: 0x1)
    uint8 bForceNetAddressable;                                                       // 0x0058 (size: 0x1)
    uint8 bExchangedRoles;                                                            // 0x0059 (size: 0x1)
    uint8 bNetLoadOnClient;                                                           // 0x0059 (size: 0x1)
    uint8 bNetUseOwnerRelevancy;                                                      // 0x0059 (size: 0x1)
    uint8 bRelevantForNetworkReplays;                                                 // 0x0059 (size: 0x1)
    uint8 bRelevantForLevelBounds;                                                    // 0x0059 (size: 0x1)
    uint8 bReplayRewindable;                                                          // 0x0059 (size: 0x1)
    uint8 bAllowTickBeforeBeginPlay;                                                  // 0x0059 (size: 0x1)
    uint8 bAutoDestroyWhenFinished;                                                   // 0x0059 (size: 0x1)
    uint8 bCanBeDamaged;                                                              // 0x005A (size: 0x1)
    uint8 bBlockInput;                                                                // 0x005A (size: 0x1)
    uint8 bCollideWhenPlacing;                                                        // 0x005A (size: 0x1)
    uint8 bFindCameraComponentWhenViewTarget;                                         // 0x005A (size: 0x1)
    uint8 bGenerateOverlapEventsDuringLevelStreaming;                                 // 0x005A (size: 0x1)
    uint8 bIgnoresOriginShifting;                                                     // 0x005A (size: 0x1)
    uint8 bEnableAutoLODGeneration;                                                   // 0x005A (size: 0x1)
    uint8 bIsEditorOnlyActor;                                                         // 0x005A (size: 0x1)
    uint8 bActorSeamlessTraveled;                                                     // 0x005B (size: 0x1)
    uint8 bReplicates;                                                                // 0x005B (size: 0x1)
    uint8 bCanBeInCluster;                                                            // 0x005B (size: 0x1)
    uint8 bAllowReceiveTickEventOnDedicatedServer;                                    // 0x005B (size: 0x1)
    uint8 bActorEnableCollision;                                                      // 0x005C (size: 0x1)
    uint8 bActorIsBeingDestroyed;                                                     // 0x005C (size: 0x1)
    EActorUpdateOverlapsMethod UpdateOverlapsMethodDuringLevelStreaming;              // 0x005D (size: 0x1)
    EActorUpdateOverlapsMethod DefaultUpdateOverlapsMethodDuringLevelStreaming;       // 0x005E (size: 0x1)
    uint8 RemoteRole;                                                 // 0x005F (size: 0x1)
    char ReplicatedMovement[0x34];                                                  // 0x0060 (size: 0x34)
    float InitialLifeSpan;                                                            // 0x0094 (size: 0x4)
    float CustomTimeDilation;                                                         // 0x0098 (size: 0x4)
    class AActor* Owner;                                                              // 0x00A0 (size: 0x8)
    void* NetDriverName;                                                              // 0x00A8 (size: 0x8)
    uint8 Role;                                                       // 0x00B0 (size: 0x1)
    uint8 NetDormancy;                                            // 0x00B1 (size: 0x1)
    ESpawnActorCollisionHandlingMethod SpawnCollisionHandlingMethod;                  // 0x00B2 (size: 0x1)
    uint8 AutoReceiveInput;                            // 0x00B3 (size: 0x1)
    int32 InputPriority;                                                              // 0x00B4 (size: 0x4)
    class UInputComponent* InputComponent;                                            // 0x00B8 (size: 0x8)
    float NetCullDistanceSquared;                                                     // 0x00C0 (size: 0x4)
    int32 NetTag;                                                                     // 0x00C4 (size: 0x4)
    float NetUpdateFrequency;                                                         // 0x00C8 (size: 0x4)
    float MinNetUpdateFrequency;                                                      // 0x00CC (size: 0x4)
    float NetPriority;                                                                // 0x00D0 (size: 0x4)
    class APawn* Instigator;                                                          // 0x00D8 (size: 0x8)
    std::vector<class AActor*> Children;                                                   // 0x00E0 (size: 0x10)
    class USceneComponent* RootComponent;                                             // 0x00F0 (size: 0x8)
    std::vector<class AMatineeActor*> ControllingMatineeActors;                            // 0x00F8 (size: 0x10)
    std::vector<void*> Layers;                                                             // 0x0110 (size: 0x10)
    void* ParentComponent;                       // 0x0120 (size: 0x8)
    TArray Tags;                                                               // 0x0130 (size: 0x10)
    void* OnTakeAnyDamage;                                            // 0x0140 (size: 0x1)
    void TakeAnyDamageSignature(class AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, class AActor* DamageCauser);
    void* OnTakePointDamage;                                        // 0x0141 (size: 0x1)
    void TakePointDamageSignature(class AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, void* BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, class AActor* DamageCauser);
    void* OnTakeRadialDamage;                                      // 0x0142 (size: 0x1)
    void TakeRadialDamageSignature(class AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, class AActor* DamageCauser);
    void* OnActorBeginOverlap;                                    // 0x0143 (size: 0x1)
    void ActorBeginOverlapSignature(class AActor* OverlappedActor, class AActor* OtherActor);
    void* OnActorEndOverlap;                                        // 0x0144 (size: 0x1)
    void ActorEndOverlapSignature(class AActor* OverlappedActor, class AActor* OtherActor);
    void* OnBeginCursorOver;                                        // 0x0145 (size: 0x1)
    void ActorBeginCursorOverSignature(class AActor* TouchedActor);
    void* OnEndCursorOver;                                            // 0x0146 (size: 0x1)
    void ActorEndCursorOverSignature(class AActor* TouchedActor);
    void* OnClicked;                                                        // 0x0147 (size: 0x1)
    void ActorOnClickedSignature(class AActor* TouchedActor, FKey ButtonPressed);
    void* OnReleased;                                                      // 0x0148 (size: 0x1)
    void ActorOnReleasedSignature(class AActor* TouchedActor, FKey ButtonReleased);
    void* OnInputTouchBegin;                                        // 0x0149 (size: 0x1)
    void ActorOnInputTouchBeginSignature(uint8 FingerIndex, void* TouchedActor);
    void* OnInputTouchEnd;                                            // 0x014A (size: 0x1)
    void ActorOnInputTouchEndSignature(uint8 FingerIndex, void* TouchedActor);
    void* OnInputTouchEnter;                                        // 0x014B (size: 0x1)
    void ActorBeginTouchOverSignature(uint8 FingerIndex, void* TouchedActor);
    void* OnInputTouchLeave;                                        // 0x014C (size: 0x1)
    void ActorEndTouchOverSignature(uint8 FingerIndex, void* TouchedActor);
    void* OnActorHit;                                                      // 0x014D (size: 0x1)
    void ActorHitSignature(class AActor* SelfActor, void* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
    void* OnDestroyed;                                                    // 0x014E (size: 0x1)
    void ActorDestroyedSignature(class AActor* DestroyedActor);
    void* OnEndPlay;                                                        // 0x014F (size: 0x1)
    void ActorEndPlaySignature(class AActor* Actor, uint8 EndPlayReason);
    TArray InstanceComponents;                                // 0x01B0 (size: 0x10)
    TArray BlueprintCreatedComponents;                        // 0x01C0 (size: 0x10)

    bool WasRecentlyRendered(float Tolerance);
    void UserConstructionScript();
    void TearOff();
    void SnapRootComponentTo(class AActor* InParentActor, void* InSocketName);
    void SetTickGroup(uint8 NewTickGroup);
    void SetTickableWhenPaused(bool bTickableWhenPaused);
    void SetReplicates(bool bInReplicates);
    void SetReplicateMovement(bool bInReplicateMovement);
    void SetOwner(class AActor* NewOwner);
    void SetNetDormancy(uint8 NewDormancy);
    void SetLifeSpan(float InLifespan);
    void SetAutoDestroyWhenFinished(bool bVal);
    void SetActorTickInterval(float TickInterval);
    void SetActorTickEnabled(bool bEnabled);
    void SetActorScale3D(FVector NewScale3D);
    void SetActorRelativeScale3D(FVector NewRelativeScale);
    void SetActorHiddenInGame(bool bNewHidden);
    void SetActorEnableCollision(bool bNewActorEnableCollision);
    void RemoveTickPrerequisiteComponent(class UActorComponent* PrerequisiteComponent);
    void RemoveTickPrerequisiteActor(class AActor* PrerequisiteActor);
    void ReceiveTick(float DeltaSeconds);
    void ReceiveRadialDamage(float DamageReceived, const class UDamageType* DamageType, FVector Origin, const FHitResult& HitInfo, class AController* InstigatedBy, class AActor* DamageCauser);
    void ReceivePointDamage(float Damage, const class UDamageType* DamageType, FVector HitLocation, FVector HitNormal, class UPrimitiveComponent* HitComponent, void* BoneName, FVector ShotFromDirection, class AController* InstigatedBy, class AActor* DamageCauser, const FHitResult& HitInfo);
    void ReceiveHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);
    void ReceiveEndPlay(uint8 EndPlayReason);
    void ReceiveDestroyed();
    void ReceiveBeginPlay();
    void ReceiveAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, class AActor* DamageCauser);
    void ReceiveActorOnReleased(FKey ButtonReleased);
    void ReceiveActorOnInputTouchLeave(const uint8 FingerIndex);
    void ReceiveActorOnInputTouchEnter(const uint8 FingerIndex);
    void ReceiveActorOnInputTouchEnd(const uint8 FingerIndex);
    void ReceiveActorOnInputTouchBegin(const uint8 FingerIndex);
    void ReceiveActorOnClicked(FKey ButtonPressed);
    void ReceiveActorEndOverlap(class AActor* OtherActor);
    void ReceiveActorEndCursorOver();
    void ReceiveActorBeginOverlap(class AActor* OtherActor);
    void ReceiveActorBeginCursorOver();
    void PrestreamTextures(float Seconds, bool bEnableStreaming, int32 CinematicTextureGroups);
    void OnRep_ReplicateMovement();
    void OnRep_ReplicatedMovement();
    void OnRep_Owner();
    void OnRep_Instigator();
    void OnRep_AttachmentReplication();
    void MakeNoise(float Loudness, class APawn* NoiseInstigator, FVector NoiseLocation, float MaxRange, void* Tag);
    class UMaterialInstanceDynamic* MakeMIDForMaterial(class UMaterialInterface* Parent);
    bool K2_TeleportTo(FVector DestLocation, FRotator DestRotation);
    bool K2_SetActorTransform(const void* NewTransform, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);
    bool K2_SetActorRotation(FRotator NewRotation, bool bTeleportPhysics);
    void K2_SetActorRelativeTransform(const void* NewRelativeTransform, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);
    void K2_SetActorRelativeRotation(FRotator NewRelativeRotation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);
    void K2_SetActorRelativeLocation(FVector NewRelativeLocation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);
    bool K2_SetActorLocationAndRotation(FVector NewLocation, FRotator NewRotation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);
    bool K2_SetActorLocation(FVector NewLocation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);
    void K2_OnReset();
    void K2_OnEndViewTarget(class APlayerController* PC);
    void K2_OnBecomeViewTarget(class APlayerController* PC);
    class USceneComponent* K2_GetRootComponent();
    TArray K2_GetComponentsByClass(void* ComponentClass);
    FRotator K2_GetActorRotation();
    FVector K2_GetActorLocation();
    void K2_DetachFromActor(EDetachmentRule LocationRule, EDetachmentRule RotationRule, EDetachmentRule ScaleRule);
    void K2_DestroyComponent(class UActorComponent* Component);
    void K2_DestroyActor();
    void K2_AttachToComponent(class USceneComponent* Parent, void* SocketName, EAttachmentRule LocationRule, EAttachmentRule RotationRule, EAttachmentRule ScaleRule, bool bWeldSimulatedBodies);
    void K2_AttachToActor(class AActor* ParentActor, void* SocketName, EAttachmentRule LocationRule, EAttachmentRule RotationRule, EAttachmentRule ScaleRule, bool bWeldSimulatedBodies);
    void K2_AttachRootComponentToActor(class AActor* InParentActor, void* InSocketName,uint8 AttachLocationType, bool bWeldSimulatedBodies);
    void K2_AttachRootComponentTo(class USceneComponent* InParent, void* InSocketName, uint8 AttachLocationType, bool bWeldSimulatedBodies);
    void K2_AddActorWorldTransformKeepScale(const void* DeltaTransform, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);
    void K2_AddActorWorldTransform(const void* DeltaTransform, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);
    void K2_AddActorWorldRotation(FRotator DeltaRotation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);
    void K2_AddActorWorldOffset(FVector DeltaLocation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);
    void K2_AddActorLocalTransform(const void* NewTransform, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);
    void K2_AddActorLocalRotation(FRotator DeltaRotation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);
    void K2_AddActorLocalOffset(FVector DeltaLocation, bool bSweep, FHitResult& SweepHitResult, bool bTeleport);
    bool IsOverlappingActor(const class AActor* Other);
    bool IsChildActor();
    bool IsActorTickEnabled();
    bool IsActorBeingDestroyed();
    bool HasAuthority();
    float GetVerticalDistanceTo(const class AActor* OtherActor);
    FVector GetVelocity();
    void* GetTransform();
    bool GetTickableWhenPaused();
    float GetSquaredHorizontalDistanceTo(const class AActor* OtherActor);
    float GetSquaredDistanceTo(const class AActor* OtherActor);
    uint8 GetRemoteRole();
    class UChildActorComponent* GetParentComponent();
    class AActor* GetParentActor();
    class AActor* GetOwner();
    void GetOverlappingComponents(TArray& OverlappingComponents);
    void GetOverlappingActors(TArray, void* ClassFilter);
    uint8 GetLocalRole();
    float GetLifeSpan();
    class AController* GetInstigatorController();
    class APawn* GetInstigator();
    FVector GetInputVectorAxisValue(const FKey InputAxisKey);
    float GetInputAxisValue(const void* InputAxisName);
    float GetInputAxisKeyValue(const FKey InputAxisKey);
    float GetHorizontalDotProductTo(const class AActor* OtherActor);
    float GetHorizontalDistanceTo(const class AActor* OtherActor);
    float GetGameTimeSinceCreation();
    float GetDotProductTo(const class AActor* OtherActor);
    float GetDistanceTo(const class AActor* OtherActor);
    std::vector<class UActorComponent*> GetComponentsByTag(void* ComponentClass, void* Tag);
    std::vector<class UActorComponent*> GetComponentsByInterface(void* Interface);
    class UActorComponent* GetComponentByClass(void* ComponentClass);
    void* GetAttachParentSocketName();
    class AActor* GetAttachParentActor();
    void GetAttachedActors(TArray& OutActors, bool bResetArray);
    void GetAllChildActors(TArray& ChildActors, bool bIncludeDescendants);
    FVector GetActorUpVector();
    float GetActorTimeDilation();
    float GetActorTickInterval();
    FVector GetActorScale3D();
    FVector GetActorRightVector();
    FVector GetActorRelativeScale3D();
    FVector GetActorForwardVector();
    void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation);
    bool GetActorEnableCollision();
    void GetActorBounds(bool bOnlyCollidingComponents, FVector& Origin, FVector& BoxExtent, bool bIncludeFromChildActors);
    void ForceNetUpdate();
    void FlushNetDormancy();
    void FinishAddComponent(class UActorComponent* Component, bool bManualAttachment, const void* RelativeTransform);
    void EnableInput(class APlayerController* PlayerController);
    void DisableInput(class APlayerController* PlayerController);
    void DetachRootComponentFromParent(bool bMaintainWorldPosition);
    void AddTickPrerequisiteComponent(class UActorComponent* PrerequisiteComponent);
    void AddTickPrerequisiteActor(class AActor* PrerequisiteActor);
    class UActorComponent* AddComponentByClass(void* Class, bool bManualAttachment, const void* RelativeTransform, bool bDeferredFinish);
    class UActorComponent* AddComponent(void* TemplateName, bool bManualAttachment, const void* RelativeTransform, const class UObject* ComponentTemplateContext, bool bDeferredFinish);
    bool ActorHasTag(void* Tag);
}; // Size: 0x1E0


class AController : public AActor
{
    class APlayerState* PlayerState;                                                  // 0x01E8 (size: 0x8)
    char OnInstigatedAnyDamage[0x10];                           // 0x01F8 (size: 0x10)
    void InstigatedAnyDamageSignature(float Damage, const class UDamageType* DamageType, class AActor* DamagedActor, class AActor* DamageCauser);
    void* StateName;                                                                  // 0x0208 (size: 0x8)
    void* Pawn;                                                                // 0x0210 (size: 0x8)
    void* Character;                                                      // 0x0220 (size: 0x8)
    void* TransformComponent;                                        // 0x0228 (size: 0x8)
    FRotator ControlRotation;                                                         // 0x0248 (size: 0xC)
    uint8 bAttachToPawn;                                                              // 0x0254 (size: 0x1)

    void UnPossess();
    void StopMovement();
    void SetInitialLocationAndRotation(const FVector& NewLocation, const FRotator& NewRotation);
    void SetIgnoreMoveInput(bool bNewMoveInput);
    void SetIgnoreLookInput(bool bNewLookInput);
    void SetControlRotation(const FRotator& NewRotation);
    void ResetIgnoreMoveInput();
    void ResetIgnoreLookInput();
    void ResetIgnoreInputFlags();
    void ReceiveUnPossess(void* UnpossessedPawn);
    void ReceivePossess(void* PossessedPawn);
    void ReceiveInstigatedAnyDamage(float Damage, const void* DamageType, void* DamagedActor, void* DamageCauser);
    void Possess(void* InPawn);
    void OnRep_PlayerState();
    void OnRep_Pawn();
    bool LineOfSightTo(const void* Other, FVector ViewPoint, bool bAlternateChecks);
    void* K2_GetPawn();
    bool IsPlayerController();
    bool IsMoveInputIgnored();
    bool IsLookInputIgnored();
    bool IsLocalPlayerController();
    bool IsLocalController();
    void* GetViewTarget();
    FRotator GetDesiredRotation();
    FRotator GetControlRotation();
    void ClientSetRotation(FRotator NewRotation, bool bResetCamera);
    void ClientSetLocation(FVector NewLocation, FRotator NewRotation);
    void* CastToPlayerController();
}; // Size: 0x258

class APlayerController : public AController
{
    void* Player;                                                            // 0x0258 (size: 0x8)
    void* AcknowledgedPawn;                                                    // 0x0260 (size: 0x8)
    void* ControllingDirTrackInst;                          // 0x0268 (size: 0x8)
    void* MyHUD;                                                                // 0x0270 (size: 0x8)
    void* PlayerCameraManager;                                  // 0x0278 (size: 0x8)
    void* PlayerCameraManagerClass;                 // 0x0280 (size: 0x8)
    bool bAutoManageActiveCameraTarget;                                               // 0x0288 (size: 0x1)
    char TargetViewRotation[0xC];                                                      // 0x028C (size: 0xC)
    float SmoothTargetViewRotationSpeed;                                              // 0x02A4 (size: 0x4)
    char pad[0x10];                                               // 0x02B0 (size: 0x10)
    char pad[0x10];            // 0x02C0 (size: 0x10)
    float LastSpectatorStateSynchTime;                                                // 0x02D4 (size: 0x4)
    float LastSpectatorSyncLocation[3];                                                // 0x02D8 (size: 0xC)
    float LastSpectatorSyncRotation[3];                                               // 0x02E4 (size: 0xC)
    int32 ClientCap;                                                                  // 0x02F0 (size: 0x4)
    void* CheatManager;                                                // 0x02F8 (size: 0x8)
    void* CheatClass;                                      // 0x0300 (size: 0x8)
    void* PlayerInput;                                                  // 0x0308 (size: 0x8)
    char pad[0x10];                    // 0x0310 (size: 0x10)
    uint8 bPlayerIsWaiting;                                                           // 0x03A0 (size: 0x1)
    uint8 NetPlayerIndex;                                                             // 0x03A4 (size: 0x1)
    void* PendingSwapConnection;                                      // 0x03E0 (size: 0x8)
    void* NetConnection;                                              // 0x03E8 (size: 0x8)
    float InputYawScale;                                                              // 0x03FC (size: 0x4)
    float InputPitchScale;                                                            // 0x0400 (size: 0x4)
    float InputRollScale;                                                             // 0x0404 (size: 0x4)
    uint8 bShowMouseCursor;                                                           // 0x0408 (size: 0x1)
    uint8 bEnableClickEvents;                                                         // 0x0408 (size: 0x1)
    uint8 bEnableTouchEvents;                                                         // 0x0408 (size: 0x1)
    uint8 bEnableMouseOverEvents;                                                     // 0x0408 (size: 0x1)
    uint8 bEnableTouchOverEvents;                                                     // 0x0408 (size: 0x1)
    uint8 bForceFeedbackEnabled;                                                      // 0x0408 (size: 0x1)
    float ForceFeedbackScale;                                                         // 0x040C (size: 0x4)
    char pad[0x10];                                                      // 0x0410 (size: 0x10)
    uint8  DefaultMouseCursor;                               // 0x0420 (size: 0x1)
    uint8  CurrentMouseCursor;                               // 0x0421 (size: 0x1)
    uint8 DefaultClickTraceChannel;                          // 0x0422 (size: 0x1)
    uint8 CurrentClickTraceChannel;                          // 0x0423 (size: 0x1)
    float HitResultTraceDistance;                                                     // 0x0424 (size: 0x4)
    uint16 SeamlessTravelCount;                                                       // 0x0428 (size: 0x2)
    uint16 LastCompletedSeamlessTravelCount;                                          // 0x042A (size: 0x2)
    void* InactiveStateInputComponent;                               // 0x04A0 (size: 0x8)
    uint8 bShouldPerformFullTickWhenPaused;                                           // 0x04A8 (size: 0x1)
    void* CurrentTouchInterface;                                     // 0x04C0 (size: 0x8)
    void* SpectatorPawn;                                              // 0x0520 (size: 0x8)
    bool bIsLocalPlayerController;                                                    // 0x052C (size: 0x1)
    float SpawnLocation[3];                                                            // 0x0530 (size: 0xC)

    bool WasInputKeyJustReleased(FKey Key);
    bool WasInputKeyJustPressed(FKey Key);
    void ToggleSpeaking(bool bInSpeaking);
    void TestServerLevelVisibilityChange(const void* PackageName, const void* Filename);
    void SwitchLevel(void* URL);
    void StopHapticEffect(EControllerHand Hand);
    void StartFire(uint8 FireModeNum);
    void SetVirtualJoystickVisibility(bool bVisible);
    void SetViewTargetWithBlend(void* NewViewTarget, float BlendTime, uint8 BlendFunc, float BlendExp, bool bLockOutgoing);
    void SetName(void* S);
    void SetMouseLocation(const int32 X, const int32 Y);
    void SetMouseCursorWidget(uint8 Cursor, void* CursorWidget);
    void SetHapticsByValue(const float Frequency, const float Amplitude, EControllerHand Hand);
    void SetDisableHaptics(bool bNewDisabled);
    void SetControllerTriggerEffect_Weapon(EControllerTriggerMask TriggerMask, uint8 StartPosition, uint8 EndPosition, uint8 Strength, bool bUseEffectForThreshold);
    void SetControllerTriggerEffect_Vibration(EControllerTriggerMask TriggerMask, uint8 position, uint8 Frequency, uint8 Amplitude, bool bUseEffectForThreshold);
    void SetControllerTriggerEffect_Feedback(EControllerTriggerMask TriggerMask, uint8 position, uint8 Strength, bool bUseEffectForThreshold);
    void SetControllerLightColor(FColor Color);
    void SetCinematicMode(bool bInCinematicMode, bool bHidePlayer, bool bAffectsHUD, bool bAffectsMovement, bool bAffectsTurning);
    void SetAudioListenerOverride(void* AttachToComponent, FVector Location, FRotator Rotation);
    void SetAudioListenerAttenuationOverride(void* AttachToComponent, FVector AttenuationLocationOVerride);
    void ServerViewSelf(FViewTargetTransitionParams TransitionParams);
    void ServerViewPrevPlayer();
    void ServerViewNextPlayer();
    void ServerVerifyViewTarget();
    void ServerUpdateMultipleLevelsVisibility(const TArray& LevelVisibilities);
    void ServerUpdateLevelVisibility(const FUpdateLevelVisibilityLevelInfo& LevelVisibility);
    void ServerUpdateCamera(FVector CamLoc, int32 CamPitchAndYaw);
    void ServerUnmutePlayer(void* PlayerId);
    void ServerToggleAILogging();
    void ServerShortTimeout();
    void ServerSetSpectatorWaiting(bool bWaiting);
    void ServerSetSpectatorLocation(FVector NewLoc, FRotator NewRot);
    void ServerRestartPlayer();
    void ServerPause();
    void ServerNotifyLoadedWorld(void* WorldPackageName);
    void ServerMutePlayer(void* PlayerId);
    void ServerExecRPC(void* Msg);
    void ServerExec(void* Msg);
    void ServerCheckClientPossessionReliable();
    void ServerCheckClientPossession();
    void ServerChangeName(void* S);
    void ServerCamera(void* NewMode);
    void ServerAcknowledgePossession(void* P);
    void SendToConsole(void* Command);
    void RestartLevel();
    void ResetControllerTriggerEffect(EControllerTriggerMask TriggerMask);
    void ResetControllerLightColor();
    bool ProjectWorldLocationToScreen(FVector WorldLocation, FVector2D& ScreenLocation, bool bPlayerViewportRelative);
    void PlayHapticEffect(void* HapticEffect, EControllerHand Hand, float Scale, bool bLoop);
    void PlayDynamicForceFeedback(float Intensity, float Duration, bool bAffectsLeftLarge, bool bAffectsLeftSmall, bool bAffectsRightLarge, bool bAffectsRightSmall, TEnumAsByte<EDynamicForceFeedbackAction::Type> Action, FLatentActionInfo LatentInfo);
    void Pause();
    void OnServerStartedVisualLogger(bool bIsLogging);
    void LocalTravel(void* URL);
    void K2_ClientPlayForceFeedback(void* ForceFeedbackEffect, void* Tag, bool bLooping, bool bIgnoreTimeDilation, bool bPlayWhilePaused);
    bool IsInputKeyDown(FKey Key);
    void GetViewportSize(int32& SizeX, int32& SizeY);
    void* GetSpectatorPawn();
    bool GetMousePosition(float& LocationX, float& LocationY);
    FVector GetInputVectorKeyState(FKey Key);
    void GetInputTouchState(uint8 FingerIndex, float& LocationX, float& LocationY, bool& bIsCurrentlyPressed);
    void GetInputMouseDelta(float& DeltaX, float& DeltaY);
    void GetInputMotionState(FVector& Tilt, FVector& RotationRate, FVector& Gravity, FVector& Acceleration);
    float GetInputKeyTimeDown(FKey Key);
    void GetInputAnalogStickState(uint8 WhichStick, float& StickX, float& StickY);
    float GetInputAnalogKeyState(FKey Key);
    void* GetHUD();
    bool GetHitResultUnderFingerForObjects(uint8 FingerIndex, const TArray& ObjectTypes, bool bTraceComplex, FHitResult& HitResult);
    bool GetHitResultUnderFingerByChannel(uint8 FingerIndex, uint8 TraceChannel, bool bTraceComplex, FHitResult& HitResult);
    bool GetHitResultUnderFinger(uint8 FingerIndex, uint8 TraceChannel, bool bTraceComplex, FHitResult& HitResult);
    bool GetHitResultUnderCursorForObjects(const TArray& ObjectTypes, bool bTraceComplex, FHitResult& HitResult);
    bool GetHitResultUnderCursorByChannel(uint8 TraceChannel, bool bTraceComplex, FHitResult& HitResult);
    bool GetHitResultUnderCursor(uint8 TraceChannel, bool bTraceComplex, FHitResult& HitResult);
    FVector GetFocalLocation();
    void FOV(float NewFOV);
    void EnableCheats();
    bool DeprojectScreenPositionToWorld(float ScreenX, float ScreenY, FVector& WorldLocation, FVector& WorldDirection);
    bool DeprojectMousePositionToWorld(FVector& WorldLocation, FVector& WorldDirection);
    void ConsoleKey(FKey Key);
    void ClientWasKicked(const FText& KickReason);
    void ClientVoiceHandshakeComplete();
    void ClientUpdateMultipleLevelsStreamingStatus(const TArray& LevelStatuses);
    void ClientUpdateLevelStreamingStatus(void* PackageName, bool bNewShouldBeLoaded, bool bNewShouldBeVisible, bool bNewShouldBlockOnLoad, int32 LODIndex);
    void ClientUnmutePlayer(void* PlayerId);
    void ClientTravelInternal(void* URL, uint8 TravelType, bool bSeamless, FGuid MapPackageGuid);
    void ClientTravel(void* URL, uint8 TravelType, bool bSeamless, FGuid MapPackageGuid);
    void ClientTeamMessage(void* SenderPlayerState, void* S, void* Type, float MsgLifeTime);
    void ClientStopForceFeedback(void* ForceFeedbackEffect, void* Tag);
    void ClientStopCameraShakesFromSource(void* SourceComponent, bool bImmediately);
    void ClientStopCameraShake(void* Shake, bool bImmediately);
    void ClientStopCameraAnim(void* AnimToStop);
    void ClientStartOnlineSession();
    void ClientStartCameraShakeFromSource(void* Shake, void* SourceComponent);
    void ClientStartCameraShake(void* Shake, float Scale, ECameraShakePlaySpace PlaySpace, FRotator UserPlaySpaceRot);
    void ClientSpawnCameraLensEffect(void* LensEffectEmitterClass);
    void ClientSetViewTarget(void* A, FViewTargetTransitionParams TransitionParams);
    void ClientSetSpectatorWaiting(bool bWaiting);
    void ClientSetHUD(void* NewHUDClass);
    void ClientSetForceMipLevelsToBeResident(void* Material, float ForceDuration, int32 CinematicTextureGroups);
    void ClientSetCinematicMode(bool bInCinematicMode, bool bAffectsMovement, bool bAffectsTurning, bool bAffectsHUD);
    void ClientSetCameraMode(void* NewCamMode);
    void ClientSetCameraFade(bool bEnableFading, FColor FadeColor, FVector2D FadeAlpha, float FadeTime, bool bFadeAudio, bool bHoldWhenFinished);
    void ClientSetBlockOnAsyncLoading();
    void ClientReturnToMainMenuWithTextReason(const FText& ReturnReason);
    void ClientReturnToMainMenu(void* ReturnReason);
    void ClientRetryClientRestart(void* NewPawn);
    void ClientRestart(void* NewPawn);
    void ClientReset();
    void ClientRepObjRef(void* Object);
    void ClientReceiveLocalizedMessage(void* Message, int32 SWITCH, void* RelatedPlayerState_1, void* RelatedPlayerState_2, void* OptionalObject);
    void ClientPrestreamTextures(class AActor* ForcedActor, float ForceDuration, bool bEnableStreaming, int32 CinematicTextureGroups);
    void ClientPrepareMapChange(void* LevelName, bool bFirst, bool bLast);
    void ClientPlaySoundAtLocation(class USoundBase* Sound, FVector Location, float VolumeMultiplier, float PitchMultiplier);
    void ClientPlaySound(class USoundBase* Sound, float VolumeMultiplier, float PitchMultiplier);
    void ClientPlayForceFeedback_Internal(void* ForceFeedbackEffect, FForceFeedbackParameters Params);
    void ClientPlayCameraAnim(void* AnimToPlay, float Scale, float Rate, float BlendInTime, float BlendOutTime, bool bLoop, bool bRandomStartTime, ECameraShakePlaySpace Space, FRotator CustomPlaySpace);
    void ClientMutePlayer(void* PlayerId);
    void ClientMessage(void* S, void* Type, float MsgLifeTime);
    void ClientIgnoreMoveInput(bool bIgnore);
    void ClientIgnoreLookInput(bool bIgnore);
    void ClientGotoState(void* NewState);
    void ClientGameEnded(void* EndGameFocus, bool bIsWinner);
    void ClientForceGarbageCollection();
    void ClientFlushLevelStreaming();
    void ClientEndOnlineSession();
    void ClientEnableNetworkVoice(bool bEnable);
    void ClientCommitMapChange();
    void ClientClearCameraLensEffects();
    void ClientCapBandwidth(int32 Cap);
    void ClientCancelPendingMapChange();
    void ClientAddTextureStreamingLoc(FVector InLoc, float Duration, bool bOverrideLocation);
    void ClearAudioListenerOverride();
    void ClearAudioListenerAttenuationOverride();
    bool CanRestartPlayer();
    void Camera(void* NewMode);
    void AddYawInput(float Val);
    void AddRollInput(float Val);
    void AddPitchInput(float Val);
    void ActivateTouchInterface(void* NewTouchInterface);
}; // Size: 0x548

#endif
