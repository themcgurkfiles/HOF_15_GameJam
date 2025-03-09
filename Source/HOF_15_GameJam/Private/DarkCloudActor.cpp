// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkCloudActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"

// Sets default values
ADarkCloudActor::ADarkCloudActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADarkCloudActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADarkCloudActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADarkCloudActor::FollowPlayer(float deltaTime)
{
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	newPosition = FMath::VInterpTo(GetActorLocation(), playerPosition, GetWorld()->GetDeltaSeconds(), cloudSpeed * deltaTime);
	SetActorLocation(newPosition);
	
	

}

