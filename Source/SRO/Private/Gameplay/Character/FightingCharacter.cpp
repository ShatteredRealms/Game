#include "Gameplay/Character/FightingCharacter.h"

#include "GameplayTagsManager.h"
#include "SROPlayerController.h"
#include "Gameplay/Attributes/CombatAttributeSet.h"
#include "Inventory/Equipment/SROEquipmentInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "SRO/SROGameplayTags.h"


AFightingCharacter::AFightingCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	EquipmentComponent = CreateDefaultSubobject<USROEquipmentComponent>(TEXT("EquipmentComponent"));
}

void AFightingCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent->AddSet<UCombatAttributeSet>();
	AbilitySystemComponent->AddSet<USkillAttributeSet>();

	if (IsLocallyControlled())
	{
		EquipmentComponent->EquipItem(DefaultNoWeapon);
	}
}

UAbilitySystemComponent* AFightingCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AFightingCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFightingCharacter, FightingTarget);
}

float AFightingCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                     AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AFightingCharacter::StartFighting(AFightingCharacter* Target)
{
	if (Target == this || !IsLocallyControlled() || Target == nullptr)
	{
		return;
	}

	HandleStartFighting(Target);
}

void AFightingCharacter::StopFighting()
{
	if (!IsLocallyControlled())
	{
		return;
	}

	if (!IsAttacking())
	{
		return;
	}
	
	HandleStopFighting();
}

bool AFightingCharacter::HandleStopFighting_Validate()
{
	if (!IsAttacking())
	{
		return false;
	}
	
	return true;
}

bool AFightingCharacter::HandleStartFighting_Validate(AFightingCharacter* Target)
{
	if (Target == this || Target == nullptr)
	{
		return false;
	}

	return true;
}

void AFightingCharacter::HandleStartFighting_Implementation(AFightingCharacter* Target)
{
	FightingTarget = Target;

	AbilitySystemComponent->SetReplicatedLooseGameplayTagCount(SROGameplayTags::Status_Fighting.GetTag(), 1);

	FGameplayTagContainer GameplayTags;
	GameplayTags.AddTag(SROGameplayTags::Status_Fighting.GetTag());
	AbilitySystemComponent->TryActivateAbilitiesByTag(GameplayTags, true);
}

void AFightingCharacter::HandleStopFighting_Implementation()
{
	// Clear fighting target
	FightingTarget = nullptr;
	
	// Update tags
	AbilitySystemComponent->SetReplicatedLooseGameplayTagCount(SROGameplayTags::Status_Fighting.GetTag(), 0);
	
	// Call BP event
	OnFightingTargetUpdated();
}

FRotator AFightingCharacter::GetFightingTargetRotation() const
{
	if (!FightingTarget)
	{
		return GetActorRotation();
	}
	
	const FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), FightingTarget->GetActorLocation());
	
	if (GetController())
	{
		FRotator ControllerRotation = GetController()->GetControlRotation();
		ControllerRotation.Yaw = Rotation.Yaw;
		return ControllerRotation;
	}

	return FRotator{0, Rotation.Yaw, 0};
}

void AFightingCharacter::OnRep_FightingTarget(AFightingCharacter* OldFightingTarget)
{
	if (IsLocallyControlled())
	{
		if (OldFightingTarget && OldFightingTarget != FightingTarget)
		{
			OldFightingTarget->GetTargetingComponent()->SetAttacked(false);
		}

		if (FightingTarget)
		{
			FightingTarget->GetTargetingComponent()->SetAttacked(true);
		}

		ASROPlayerController* PC = Cast<ASROPlayerController>(GetController());
		PC->UpdateTargetingUI();
	}
	
	OnFightingTargetUpdated();
}

void AFightingCharacter::OnFightingTargetUpdated_Implementation()
{
}