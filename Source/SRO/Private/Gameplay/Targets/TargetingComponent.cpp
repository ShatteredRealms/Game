// Copyright Shattered Realms Online All Rights Reserved


#include "Gameplay/Targets/TargetingComponent.h"

#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SRO/SRO.h"
#include "UI/Targeting/TargetDetailsWidget.h"

UTargetingComponent::UTargetingComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UTargetDetailsWidget> FoundTargetDetailsWidget(TEXT("/Game/SRO/Core/UI/Targeting/BP_TargetDetails"));
	if (FoundTargetDetailsWidget.Class)
	{
		SetWidgetClass(FoundTargetDetailsWidget.Class);
	}
	
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> FoundMaterial(TEXT("/Game/SRO/Core/UI/Materials/Widget3DPassThrough_FaceCamera"));
	if (FoundMaterial.Succeeded())
	{
		SetMaterial(0, FoundMaterial.Object);
	}

	SetUsingAbsoluteRotation(true);
	bDrawAtDesiredSize = true;
}

void UTargetingComponent::BeginPlay()
{
	Super::BeginPlay();

	// Not needed on the server
	if (GetOwner()->HasAuthority())
	{
		return;
	}
	
	if (!GetWidgetClass())
	{
		UE_LOG(LogSRO, Error, TEXT("Target details widget not found"))
		return;
	}

	if (!GetWidgetClass()->IsChildOf(UTargetDetailsWidget::StaticClass()))
	{
		UE_LOG(LogSRO, Error, TEXT("Target details widget not of type UTargetDetailsWidget"))
		return;
	}
}

void UTargetingComponent::SetTargeted(bool bIsTargeted)
{
	GetDetailsUserWidget()->SetTargeted(bIsTargeted);
}

bool UTargetingComponent::IsTargeted()
{
	return GetDetailsUserWidget()->IsTargeted();
}

void UTargetingComponent::SetAttacked(bool bNewAttacked)
{
	return GetDetailsUserWidget()->SetAttacked(bNewAttacked);
}

bool UTargetingComponent::IsAttacked()
{
	return GetDetailsUserWidget()->IsAttacked();
}

void UTargetingComponent::SetDisplayName(FString NewName)
{
	GetDetailsUserWidget()->SetDisplayName(NewName);
}

UTargetDetailsWidget* UTargetingComponent::GetDetailsUserWidget()
{
	return Cast<UTargetDetailsWidget>(GetUserWidgetObject());
}

void UTargetingComponent::Setup(AActor* Actor)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(Actor->GetWorld(), 0);
	if (PC && PC->IsLocalPlayerController())
	{
		UTargetDetailsWidget* NewWidget = CreateWidget<UTargetDetailsWidget>(Actor->GetWorld(), GetWidgetClass());
		NewWidget->Setup(Actor);
		SetWidget(NewWidget);
	}
}
