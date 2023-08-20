#include "Gameplay/Character/FightingCharacter.h"

#include "GameplayTagsManager.h"
#include "Gameplay/Attributes/CombatAttributeSet.h"
#include "Gameplay/Combat/Abilities/BasicAttack.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "SRO/SROGameplayTags.h"

AFightingCharacter::AFightingCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	CombatAttributes = CreateDefaultSubobject<UCombatAttributeSet>(TEXT("CombatAttributes"));
	SkillAttributes = CreateDefaultSubobject<USkillAttributeSet>(TEXT("SKillAttributes"));
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
	if (Target == this || !IsLocallyControlled())
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
	
	HandleStopFighting();
}

void AFightingCharacter::HandleStartFighting_Implementation(AFightingCharacter* Target)
{
	FightingTarget = Target;
	if (FightingTarget)
	{
		// FGameplayAbilitySpec* BasicAttackSpec = GetAbilitySystemComponent()->FindAbilitySpecFromInputID(
		// 	UBasicAttack::StaticClass()->GetDefaultObject<UBasicAttack>()->GetAbilityId());
		// if (BasicAttackSpec)
		// {
		// 	GetAbilitySystemComponent()->TryActivateAbility(BasicAttackSpec->Handle);
		// }

		AbilitySystemComponent->SetReplicatedLooseGameplayTagCount(SROGameplayTags::Status_Fighting.GetTag(), 1);
	}
}

void AFightingCharacter::HandleStopFighting_Implementation()
{
	FightingTarget = nullptr;
	AbilitySystemComponent->SetReplicatedLooseGameplayTagCount(SROGameplayTags::Status_Fighting.GetTag(), 0);
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
	}
	
	OnFightingTargetUpdated();
}

void AFightingCharacter::OnFightingTargetUpdated_Implementation()
{
}