// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueVidrio.h"

ABloqueVidrio::ABloqueVidrio()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/StarterContent/Materials/M_Glass.M_Glass'"));
	if (Material.Succeeded())
	{
		MallaBloque->SetMaterial(0, Material.Object);
	}
	FloatSpeed =3.0f;
	RotationSpeed = 3.0f;
	bPuedeMoverse = false;
}

void ABloqueVidrio::BeginPlay()
{
	Super::BeginPlay();
	PosicionInicial = GetActorLocation();
}

void ABloqueVidrio::Tick(float DeltaTime)
{
	if (bPuedeMoverse)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.X = PosicionInicial.X + FMath::Sin(GetGameTimeSinceCreation() * FloatSpeed) * 100.0f + 0.0f;
		NewLocation.Y = PosicionInicial.Y + FMath::Cos(GetGameTimeSinceCreation() * FloatSpeed) * 100.0f + 0.0f;
		SetActorLocation(NewLocation);
	}
}
