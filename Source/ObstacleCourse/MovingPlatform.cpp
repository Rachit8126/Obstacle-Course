// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if(PlatformShouldReturn())
	{
		FVector MovDir = velocity.GetSafeNormal();
		StartLocation += MovDir * maxDis;
		SetActorLocation(StartLocation);
		velocity = -velocity;
	}
	else
	{
		FVector currLocation = GetActorLocation();
		currLocation += velocity * DeltaTime;
		SetActorLocation(currLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}
 
bool AMovingPlatform::PlatformShouldReturn() const
{
	float dis = FVector::Distance(GetActorLocation(), StartLocation);
	return dis > maxDis;
}
