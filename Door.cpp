// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "Encounter.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	// set positions
	Super::BeginPlay();
	CurrentPosition = this->GetActorLocation();
	OpenPosition=CurrentPosition;
	AActor* temp = 	this->GetParentActor();
	AEncounter* Encounter = Cast<AEncounter>(temp);

	if(temp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Parent IS %s"), *temp->GetName());
		//add this door to whatever encounter it is a part of 
		if(isEntrance)
		{
			Encounter->EntranceDoor = this;

		}
		else
		{
			Encounter->ExitDoor = this;
		}
	}



	
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//move door when entering or leaving encounter depending on if its exit or entrance
	FVector temp =FMath::Lerp(this->GetActorLocation() , CurrentPosition ,DoorClosingSpeed);
	
	this->SetActorLocation( temp , false,false,ETeleportType::TeleportPhysics);

}

//set the door to be opened
void ADoor::OpenDoor()
{
	GEngine -> AddOnScreenDebugMessage(-1 , 10.f , FColor:: Blue, "Open Sesame");

	CurrentPosition = OpenPosition;
	
}

//set the door to be closed
void ADoor::CloseDoor()
{
	GEngine -> AddOnScreenDebugMessage(-1 , 10.f , FColor:: Blue, "Close Sesame");

	
	CurrentPosition = this->GetActorLocation()+ FVector (0,0,ClosedOffSet);
	
	
}

