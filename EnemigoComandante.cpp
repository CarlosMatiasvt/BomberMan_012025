// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoComandante.h"



AEnemigoComandante::AEnemigoComandante()
{
	ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("Texture2D'/Game/Mannequin/Character/Materials/MaterialLayers/T_ML_Rubber_Blue_01_D.T_ML_Rubber_Blue_01_D'"));
	if (MaterialAsset.Succeeded())
	{
		GetMesh()->SetMaterial(0, MaterialAsset.Object);
	}
}
