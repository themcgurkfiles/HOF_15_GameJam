// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkCloudActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "DrawDebugHelpers.h"

// Sets default values
ADarkCloudActor::ADarkCloudActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	playerCharacter = nullptr;
}

// Called when the game starts or when spawned
void ADarkCloudActor::BeginPlay()
{
	Super::BeginPlay();
	cloudSpeed = 100.f;

	playerCharacter = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ADarkCloudActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWorld* world = GetWorld();

	DrawDebugSphere(world, GetActorLocation(), 35.f, 25, FColor::Blue, false, -1.f);
	FVector playerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	if (playerCharacter)
	{
		FVector Direction = playerPosition - GetActorLocation();
		Direction.Normalize();
		FVector NewLocation = GetActorLocation() + (Direction * cloudSpeed * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

