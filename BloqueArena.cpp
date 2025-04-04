// Fill out your copyright notice in the Description page of Project Settings.


#include "BloqueArena.h"

ABloqueArena::ABloqueArena()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Rust.M_Metal_Rust'"));
	if (Material.Succeeded())
	{
		MallaBloque->SetMaterial(0, Material.Object);
	}
	FloatSpeed = 3.0f;
	RotationSpeed = 3.0f;
	bPuedeMoverse = false;
}


