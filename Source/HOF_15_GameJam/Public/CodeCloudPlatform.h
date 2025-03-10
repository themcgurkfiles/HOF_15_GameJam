// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "CodeCloudPlatform.generated.h"


UCLASS()
class HOF_15_GAMEJAM_API ACodeCloudPlatform : public AActor
{
	GENERATED_BODY()
public:
    ACodeCloudPlatform();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void StartFading();
    void StopFading();
    void ChargePlatform();
    void FadeOtherPlatforms();

    UFUNCTION()
    void OnPlayerStep(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloud Platform")
    bool isCharged = false;

private:
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* PlatformMesh;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* CollisionBox;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* DamageFloor;

	UPROPERTY(VisibleAnywhere)
    UMaterialInstanceDynamic* DynamicMaterial;

    FTimerHandle FadeTimerHandle;
    float FadeProgress = 1.0f;
    bool bIsFading = false;

};
