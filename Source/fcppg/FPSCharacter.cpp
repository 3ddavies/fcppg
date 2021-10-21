// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "Engine/World.h"//just to avoid errors.
#include "DamageableActor.h"
// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



void AFPSCharacter::fireWeapon()
{
	FHitResult hit = instantShot();
	ADamageableActor* hitActor = Cast<ADamageableActor>(hit.Actor);
	if (hitActor && hitActor->isAttackable)
	{
		hitActor->takeAttack();
	}
}



FHitResult AFPSCharacter::instantShot()
{
	FVector rayLocation;//get camera location. aka where the person is looking and where the object will be shot from. this is the middle of screen. if shooting from a gun we would choose different location such as the tip of the gun and its rotation.
	FRotator rayRotation;//get cam location and figure out which way is foward.
	FVector endTrace = FVector::ZeroVector;//where we want the line to end, ie weapon range. zero vector inits it to 0,0,0


	APlayerController* const playerController = GetWorld()->GetFirstPlayerController();
	if (playerController)
	{
		playerController->GetPlayerViewPoint(rayLocation, rayRotation);//basically gets the location of where the player is looking
		//we need to know where we facing and where we standing. then add a distiance from where i standing to the direction the projectile is going.
		endTrace = rayLocation + (rayRotation.Vector() * weaponRange);//the 1000 is the weapon range. calling .vector on the rotation gets the foward rotation.
	}

	FCollisionQueryParams traceParams(SCENE_QUERY_STAT(instantShot), true, GetInstigator()); // instigator ignores person shooting so they dopnt shoot they own hand
	FHitResult hit(ForceInit); //hit result 0 unless something actually hits.
	GetWorld()->LineTraceSingleByChannel(hit, rayLocation, endTrace, ECC_Visibility, traceParams);//ecc_visab shit basically means it can hit everything visable.
	return hit;
}