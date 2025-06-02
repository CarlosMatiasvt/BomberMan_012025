// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoBase2.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"

// Sets default values
AEnemigoBase2::AEnemigoBase2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Configuración del movimiento
	GetCharacterMovement()->MaxWalkSpeed = VelocidadMovimiento;
	// Configuración de la malla
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	}
	// Poseído automáticamente por IA al colocarlo o spawnearlo
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Controlador por defecto
	AIControllerClass = AAIController::StaticClass();
}

// Called when the game starts or when spawned
void AEnemigoBase2::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerMovimiento, this, &AEnemigoBase2::MoverAleatoriamente, TiempoEntreMovimientos, true);

	
}

void AEnemigoBase2::MoverAleatoriamente()
{
	// Verifica si hay posiciones libres disponibles
	if (PosicionesLibres.Num() == 0) return;
	// Selecciona un destino aleatorio
	int32 Indice = FMath::RandRange(0, PosicionesLibres.Num() - 1);
	FVector Destino = PosicionesLibres[Indice];
	// Controlador IA
	AAIController* AI = Cast<AAIController>(GetController());
	if (AI)
	{
		// Mueve al enemigo a la posición seleccionada
		AI->MoveToLocation(Destino);
	}
}

// Called every frame
void AEnemigoBase2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemigoBase2::SetPosicionesLibres(const TArray<FVector>& NuevasPosiciones)
{
	PosicionesLibres = NuevasPosiciones;
}

// Called to bind functionality to input
void AEnemigoBase2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

