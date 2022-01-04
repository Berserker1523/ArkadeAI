// Fill out your copyright notice in the Description page of Project Settings.


#include "STS_Weapon.h"
#include "Components/StaticMeshComponent.h"
#include <ARK_StealthShooter/ARK_StealthShooter.h>
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASTS_Weapon::ASTS_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = WeaponMesh;
	ShotDistance = 10000.f;
	ShotDamage = 20.f;
}

void ASTS_Weapon::Fire()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotDirection = EyeRotation.Vector();

		FVector TraceEnd = EyeLocation + (ShotDirection * ShotDistance);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, WEAPON_COLLISION, QueryParams))
		{
			AActor* HitActor = Hit.GetActor();
			UGameplayStatics::ApplyPointDamage(
				HitActor, 
				ShotDamage, 
				ShotDirection, 
				Hit, 
				MyOwner->GetInstigatorController(), 
				MyOwner, 
				DamageType);
			DrawDebugLine(GetWorld(), EyeLocation, Hit.ImpactPoint, FColor::White, false, 1.0f, 0, 1.0f);
		}
	}
}

// Called when the game starts or when spawned
void ASTS_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}
