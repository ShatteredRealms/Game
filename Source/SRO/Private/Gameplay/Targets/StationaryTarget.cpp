// Copyright Shattered Realms Online All Rights Reserved


#include "Gameplay/Targets/StationaryTarget.h"

AStationaryTarget::AStationaryTarget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateOptionalDefaultSubobject<UStaticMeshComponent>(TEXT("TargetMesh0"));
	if (Mesh)
	{
		RootComponent = Mesh;
		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->bOwnerNoSee = false;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		static FName MeshCollisionProfileName(TEXT("TargetMesh"));
		Mesh->SetCollisionProfileName(MeshCollisionProfileName);
		Mesh->SetGenerateOverlapEvents(false);
		Mesh->SetCanEverAffectNavigation(false);
	}

	TargetingComponent = CreateDefaultSubobject<UTargetingComponent>(TEXT("TargetingComponent"));
	TargetingComponent->SetupAttachment(RootComponent);
}

void AStationaryTarget::BeginPlay()
{
	Super::BeginPlay();
	TargetingComponent->Setup(this);
}

UTargetingComponent* AStationaryTarget::GetTargetingComponent()
{
	return TargetingComponent;
}

void AStationaryTarget::SetDisplayName(FString NewDisplayName)
{
	DisplayName = NewDisplayName;
	TargetingComponent->SetDisplayName(NewDisplayName);
}
