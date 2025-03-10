// Fill out your copyright notice in the Description page of Project Settings.

#include "LightningBolt.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALightningBolt::ALightningBolt()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create Mesh
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    // Create Projectile Movement
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->ProjectileGravityScale = 1.0f;
    ProjectileMovement->InitialSpeed = 0.0f;
    ProjectileMovement->MaxSpeed = 5000.0f;
    ProjectileMovement->bShouldBounce = false;

    // Enable collision handling
    MeshComponent->SetSimulatePhysics(false);
    MeshComponent->SetCollisionProfileName(TEXT("BlockAll"));
    MeshComponent->OnComponentHit.AddDynamic(this, &ALightningBolt::OnHit);
}

// Called when the game starts or when spawned
void ALightningBolt::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALightningBolt::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALightningBolt::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Check if other actor is cloud platform class


    
    if (OtherActor && OtherActor != this)
    {
        // Example damage
        UGameplayStatics::ApplyDamage(OtherActor, 1.0f, GetInstigatorController(), this, nullptr);
        Destroy();
    }
}

