// Copyright Shattered Realms Online All Rights Reserved


#include "Gameplay/Attributes/SkillAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Gameplay/Attributes/AttributeHelpers.h"
#include "Net/UnrealNetwork.h"
#include "SRO/SRO.h"

FGameplayAttributeData& USkillAttributeSet::GetAttributeData(ESkill Skill)
{
	switch (Skill)
	{
	case ESkill::Strength: return Strength;
	case ESkill::Stamina: return Stamina;
	case ESkill::Agility: return Agility;
	case ESkill::Perception: return Perception;
	case ESkill::Intelligence: return Intelligence;
	case ESkill::Insight: return Insight;
	case ESkill::MartialArts: return MartialArts;
	case ESkill::OneHandMelee: return OneHandMelee;
	case ESkill::TwoHandMelee: return TwoHandMelee;
	case ESkill::MultiMelee: return MultiMelee;
	case ESkill::MeleeInitiative: return MeleeInitiative;
	case ESkill::QuickSlash: return QuickSlash;
	case ESkill::Smash: return Smash;
	case ESkill::Flurry: return Flurry;
	case ESkill::Pistol: return Pistol;
	case ESkill::Rifle: return Rifle;
	case ESkill::Sniper: return Sniper;
	case ESkill::RangedInitiative: RangedInitiative;
	case ESkill::QuickShot: return QuickSlash;
	case ESkill::PrecisionShot: return PrecisionShot;
	case ESkill::Burst: return Burst;
	case ESkill::Creation: return Creation;
	case ESkill::Metamorphosis: return Metamorphosis;
	case ESkill::Remedy: return Remedy;
	case ESkill::Rejuvenation: return Rejuvenation;
	case ESkill::SpaceTime: return SpaceTime;
	case ESkill::Enhancement: return Enhancement;
	case ESkill::MagicInitiative: return MagicInitiative;
	case ESkill::Programming: return Programming;
	case ESkill::Construction: return Construction;
	case ESkill::Engineering: return Engineering;
	case ESkill::LockPicking: return LockPicking;
	case ESkill::Treatment: return Treatment;
	case ESkill::FirstAid: return FirstAid;
	case ESkill::Constitution: return Constitution;
	case ESkill::ManaPool: return ManaPool;
	case ESkill::MovementSpeed: return MovementSpeed;
	default:
		UE_LOG(LogSRO, Error, TEXT("Unknown SkillAttribute enum"))
		return Unknown;
	}
}

void USkillAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Strength,			COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Stamina,				COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Agility,				COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Perception,			COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Intelligence,		COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Insight,				COND_OwnerOnly, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, MartialArts,			COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, OneHandMelee,		COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, TwoHandMelee,		COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, MultiMelee,			COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, MeleeInitiative,		COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, QuickSlash,			COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Smash,				COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Flurry,				COND_OwnerOnly, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Pistol,				COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Rifle,				COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Sniper,				COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, RangedInitiative,	COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, QuickShot,			COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, PrecisionShot,		COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Burst,				COND_OwnerOnly, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Creation,			COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Metamorphosis,		COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Remedy,				COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Rejuvenation,		COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, SpaceTime,			COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Enhancement,			COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, MagicInitiative,		COND_OwnerOnly, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Programming,			COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Construction,		COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Engineering,			COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, LockPicking,			COND_OwnerOnly, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Treatment,			COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, FirstAid,			COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, Constitution,		COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, ManaPool,			COND_OwnerOnly, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(USkillAttributeSet, MovementSpeed,		COND_OwnerOnly, REPNOTIFY_Always);
}

void USkillAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

		GA_SET_IF(Strength,			-1000, 2000)
	GA_SET_ELSEIF(Stamina,			-1000, 2000)
	GA_SET_ELSEIF(Agility,			-1000, 2000)
	GA_SET_ELSEIF(Perception,		-1000, 2000)
	GA_SET_ELSEIF(Intelligence,		-1000, 2000)
	GA_SET_ELSEIF(Insight,			-1000, 2000)
	GA_SET_ELSEIF(MartialArts,		-1000, 2000)
	GA_SET_ELSEIF(OneHandMelee,		-1000, 2000)
	GA_SET_ELSEIF(OneHandMelee,		-1000, 2000)
	GA_SET_ELSEIF(TwoHandMelee,		-1000, 2000)
	GA_SET_ELSEIF(MultiMelee,		-1000, 2000)
	GA_SET_ELSEIF(MeleeInitiative,	-1000, 2000)
	GA_SET_ELSEIF(QuickSlash,		-1000, 2000)
	GA_SET_ELSEIF(Smash,			-1000, 2000)
	GA_SET_ELSEIF(Flurry,			-1000, 2000)
	GA_SET_ELSEIF(Pistol,			-1000, 2000)
	GA_SET_ELSEIF(Rifle,			-1000, 2000)
	GA_SET_ELSEIF(Sniper,			-1000, 2000)
	GA_SET_ELSEIF(RangedInitiative,	-1000, 2000)
	GA_SET_ELSEIF(QuickShot,		-1000, 2000)
	GA_SET_ELSEIF(PrecisionShot,	-1000, 2000)
	GA_SET_ELSEIF(Burst,			-1000, 2000)
	GA_SET_ELSEIF(Creation,			-1000, 2000)
	GA_SET_ELSEIF(Metamorphosis,	-1000, 2000)
	GA_SET_ELSEIF(Remedy,			-1000, 2000)
	GA_SET_ELSEIF(Rejuvenation,		-1000, 2000)
	GA_SET_ELSEIF(SpaceTime,		-1000, 2000)
	GA_SET_ELSEIF(Enhancement,		-1000, 2000)
	GA_SET_ELSEIF(MagicInitiative,	-1000, 2000)
	GA_SET_ELSEIF(Programming,		-1000, 2000)
	GA_SET_ELSEIF(Construction,		-1000, 2000)
	GA_SET_ELSEIF(Engineering,		-1000, 2000)
	GA_SET_ELSEIF(LockPicking,		-1000, 2000)
	GA_SET_ELSEIF(Treatment,		-1000, 2000)
	GA_SET_ELSEIF(FirstAid,			-1000, 2000)
	GA_SET_ELSEIF(Constitution,		-1000, 2000)
	GA_SET_ELSEIF(ManaPool,			-1000, 2000)
	GA_SET_ELSEIF(MovementSpeed,	-1000, 2000)
}

void USkillAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Strength, OldStrength);
}

void USkillAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Stamina, OldStamina);
}

void USkillAttributeSet::OnRep_Agility(const FGameplayAttributeData& OldAgility)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Agility, OldAgility);
}

void USkillAttributeSet::OnRep_Perception(const FGameplayAttributeData& OldPerception)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Perception, OldPerception);
}

void USkillAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Intelligence, OldIntelligence);
}

void USkillAttributeSet::OnRep_Insight(const FGameplayAttributeData& OldInsight)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Insight, OldInsight);
}

void USkillAttributeSet::OnRep_MartialArts(const FGameplayAttributeData& OldMartialArts)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, MartialArts, OldMartialArts);
}

void USkillAttributeSet::OnRep_OneHandMelee(const FGameplayAttributeData& OldOneHandMelee)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, OneHandMelee, OldOneHandMelee);
}

void USkillAttributeSet::OnRep_TwoHandMelee(const FGameplayAttributeData& OldTwoHandMelee)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, TwoHandMelee, OldTwoHandMelee);
}

void USkillAttributeSet::OnRep_MultiMelee(const FGameplayAttributeData& OldMultiMelee)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, MultiMelee, OldMultiMelee);
}

void USkillAttributeSet::OnRep_MeleeInitiative(const FGameplayAttributeData& OldMeleeInitiative)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, MeleeInitiative, OldMeleeInitiative);
}

void USkillAttributeSet::OnRep_QuickSlash(const FGameplayAttributeData& OldQuickSlash)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, QuickSlash, OldQuickSlash);
}

void USkillAttributeSet::OnRep_Smash(const FGameplayAttributeData& OldSmash)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Smash, OldSmash);
}

void USkillAttributeSet::OnRep_Flurry(const FGameplayAttributeData& OldFlurry)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Flurry, OldFlurry);
}

void USkillAttributeSet::OnRep_Pistol(const FGameplayAttributeData& OldPistol)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Pistol, OldPistol);
}

void USkillAttributeSet::OnRep_Rifle(const FGameplayAttributeData& OldRifle)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Rifle, OldRifle);
}

void USkillAttributeSet::OnRep_Sniper(const FGameplayAttributeData& OldSniper)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Sniper, OldSniper);
}

void USkillAttributeSet::OnRep_RangedInitiative(const FGameplayAttributeData& OldRangedInitiative)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, RangedInitiative, OldRangedInitiative);
}

void USkillAttributeSet::OnRep_QuickShot(const FGameplayAttributeData& OldQuickShot)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, QuickShot, OldQuickShot);
}

void USkillAttributeSet::OnRep_PrecisionShot(const FGameplayAttributeData& OldPrecisionShot)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, PrecisionShot, OldPrecisionShot);
}

void USkillAttributeSet::OnRep_Burst(const FGameplayAttributeData& OldBurst)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Burst, OldBurst);
}

void USkillAttributeSet::OnRep_Creation(const FGameplayAttributeData& OldCreation)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Creation, OldCreation);
}

void USkillAttributeSet::OnRep_Metamorphosis(const FGameplayAttributeData& OldMetamorphosis)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Metamorphosis, OldMetamorphosis);
}

void USkillAttributeSet::OnRep_Remedy(const FGameplayAttributeData& OldRemedy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Remedy, OldRemedy);
}

void USkillAttributeSet::OnRep_Rejuvenation(const FGameplayAttributeData& OldRejuvenation)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Rejuvenation, OldRejuvenation);
}

void USkillAttributeSet::OnRep_SpaceTime(const FGameplayAttributeData& OldSpaceTime)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, SpaceTime, OldSpaceTime);
}

void USkillAttributeSet::OnRep_Enhancement(const FGameplayAttributeData& OldEnhancement)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Enhancement, OldEnhancement);
}

void USkillAttributeSet::OnRep_MagicInitiative(const FGameplayAttributeData& OldMagicInitiative)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, MagicInitiative, OldMagicInitiative);
}

void USkillAttributeSet::OnRep_Programming(const FGameplayAttributeData& OldProgramming)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Programming, OldProgramming);
}

void USkillAttributeSet::OnRep_Construction(const FGameplayAttributeData& OldConstruction)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Construction, OldConstruction);
}

void USkillAttributeSet::OnRep_Engineering(const FGameplayAttributeData& OldEngineering)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Engineering, OldEngineering);
}

void USkillAttributeSet::OnRep_LockPicking(const FGameplayAttributeData& OldLockPicking)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, LockPicking, OldLockPicking);
}

void USkillAttributeSet::OnRep_Treatment(const FGameplayAttributeData& OldTreatment)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Treatment, OldTreatment);
}

void USkillAttributeSet::OnRep_FirstAid(const FGameplayAttributeData& OldFirstAid)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, FirstAid, OldFirstAid);
}

void USkillAttributeSet::OnRep_Constitution(const FGameplayAttributeData& OldConstitution)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, Constitution, OldConstitution);
}

void USkillAttributeSet::OnRep_ManaPool(const FGameplayAttributeData& OldManaPool)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, ManaPool, OldManaPool);
}

void USkillAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(USkillAttributeSet, MovementSpeed, OldMovementSpeed);
}
