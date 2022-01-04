// Fill out your copyright notice in the Description page of Project Settings.


#include "STS_BaseCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include <STS_Weapon.h>

// Sets default values
ASTS_BaseCharacter::ASTS_BaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void ASTS_BaseCharacter::StartFire()
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->Fire();
	}
}

// Called when the game starts or when spawned
void ASTS_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(StartingWeaponClass))
	{
		CurrentWeapon = GetWorld()->SpawnActor<ASTS_Weapon>(StartingWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeapoNSocketName);
		}
	}
}
