// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bloque.generated.h"

class UStaticMeshComponent;

UCLASS()
class BOMBERMAN_012025_API ABloque : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABloque();

	UStaticMeshComponent* MallaBloque;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float FloatSpeed;
	float RotationSpeed;
	bool bPuedeMoverse;
	FVector PosicionInicial;
	//Factory method
	static ABloque* CreateBloque(UWorld* World, const FVector& Location, const FRotator& Rotation)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		return World->SpawnActor<ABloque>(Location, Rotation, SpawnParams);
	} //esto hace que se pueda crear un bloque desde cualquier parte del juego 
	//sin necesidad de tener una referencia a la clase Bloque directamente

};
