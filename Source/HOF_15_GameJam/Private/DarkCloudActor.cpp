// Fill out your copyright notice in the Description page of Project Settings.


#include "DarkCloudActor.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"
#include "NiagaraComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "TimerManager.h"



// Sets default values
ADarkCloudActor::ADarkCloudActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	player = nullptr;
	niagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	niagaraComponent->SetupAttachment(RootComponent); // Attach it to the root or another component
}

// Called when the game starts or when spawned
void ADarkCloudActor::BeginPlay()
{
	Super::BeginPlay();
	cloudSpeed = 250.f;

	player = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	// Load the Niagara system dynamically
	UNiagaraSystem* LoadedNiagaraSystem = Cast<UNiagaraSystem>(StaticLoadObject(
		UNiagaraSystem::StaticClass(),
		nullptr,
		TEXT("/Game/Developers/pccas/Niagara/Particles/NiagaraSystems/NS_DarkCloud")

	));

	if (LoadedNiagaraSystem)
	{
		if (niagaraComponent)
		{
			niagaraComponent->SetAsset(LoadedNiagaraSystem);
			niagaraComponent->ActivateSystem();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load Niagara system asset at runtime!"));
	}

	
	
}



// Called every frame
void ADarkCloudActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWorld* world = GetWorld();

	FVector playerPosition = world->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	if (player)
	{
		FVector direction = playerPosition - GetActorLocation();
		direction.Normalize();
		FVector newLocation = GetActorLocation() + (direction * cloudSpeed * DeltaTime);
		SetActorLocation(newLocation);

		

	}
}

