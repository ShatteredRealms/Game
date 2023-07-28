// Copyright Shattered Realms Online All Rights Reserved


#include "Gameplay/Combat/Damage/MeleeDamage.h"

UMeleeDamage::UMeleeDamage()
{
	bCausedByWorld = 0;
	bScaleMomentumByMass = 0;
	bRadialDamageVelChange = 0;
	DamageImpulse = 1;
	DestructibleImpulse = 1;
	DestructibleDamageSpreadScale = 1;
	DamageFalloff = 1;
}
