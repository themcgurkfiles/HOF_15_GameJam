// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeCloudPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACodeCloudPlatform::ACodeCloudPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    RootComponent = PlatformMesh;

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(RootComponent);
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACodeCloudPlatform::OnPlayerStep);

    DamageFloor = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageFloor"));
    DamageFloor->SetupAttachment(RootComponent);
    DamageFloor->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Start disabled
    DamageFloor->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void ACodeCloudPlatform::BeginPlay()
{
	Super::BeginPlay();
    DynamicMaterial = PlatformMesh->CreateAndSetMaterialInstanceDynamic(0);
    if (DynamicMaterial)
    {
        DynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), FadeProgress);
    }
}

// Called every frame
void ACodeCloudPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsFading && !isCharged)
    {
        FadeProgress -= DeltaTime * 0.5f;
        if (FadeProgress <= 0.0f)
        {
            SetActorEnableCollision(false);
            PlatformMesh->SetVisibility(false);
            bIsFading = false;
        }
        else
        {
            PlatformMesh->SetScalarParameterValueOnMaterials(TEXT("Opacity"), FadeProgress);
        }
    }

    if (DynamicMaterial)
    {
        DynamicMaterial->SetScalarParameterValue(TEXT("Opacity"), FadeProgress);
    }
}

void ACodeCloudPlatform::StartFading()
{
    if (!isCharged)
    {
        bIsFading = true;
        GetWorldTimerManager().SetTimer(FadeTimerHandle, this, &ACodeCloudPlatform::StopFading, 2.0f, false);
    }
}

void ACodeCloudPlatform::StopFading()
{
    bIsFading = false;
    SetActorEnableCollision(true);
    PlatformMesh->SetVisibility(true);
    FadeProgress = 1.0f;
    PlatformMesh->SetScalarParameterValueOnMaterials(TEXT("Opacity"), 1.0f);
}

void ACodeCloudPlatform::ChargePlatform()
{
    isCharged = true;
    DamageFloor->SetActive(true);
    StopFading();
    FadeOtherPlatforms();
}

void ACodeCloudPlatform::FadeOtherPlatforms()
{
    TArray<AActor*> Platforms;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACodeCloudPlatform::StaticClass(), Platforms);

    for (AActor* Platform : Platforms)
    {
        ACodeCloudPlatform* Cloud = Cast<ACodeCloudPlatform>(Platform);
        if (Cloud && Cloud != this && !Cloud->bIsFading)
        {
            Cloud->StartFading();
        }
    }
}

void ACodeCloudPlatform::OnPlayerStep(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    StopFading();
    StartFading();
}
