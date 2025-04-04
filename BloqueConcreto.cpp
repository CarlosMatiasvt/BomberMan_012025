// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueConcreto.h"

ABloqueConcreto::ABloqueConcreto()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/StarterContent/Materials/M_Concrete_Tiles.M_Concrete_Tiles'"));
	if (Material.Succeeded())
	{
		MallaBloque->SetMaterial(0, Material.Object);
	}
	FloatSpeed = 3.0f;
	RotationSpeed = 3.0f;
	bPuedeMoverse = FMath::RandBool();

};

void ABloqueConcreto::BeginPlay()
{
	Super::BeginPlay();
	PosicionInicial = GetActorLocation();
}

void ABloqueConcreto::Tick(float DeltaTime)
{
	if (bPuedeMoverse)
	{
		FVector NewLocation = PosicionInicial;
		NewLocation.X = PosicionInicial.X+FMath::Sin(GetGameTimeSinceCreation() * FloatSpeed) * 100.0f;
		SetActorLocation(NewLocation);
	}
}