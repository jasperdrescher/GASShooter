// Copyright 2024 Dan Kestranek.


#include "Characters/GSASCActorBase.h"
#include "Characters/Abilities/GSAbilitySystemComponent.h"

// Sets default values
AGSASCActorBase::AGSASCActorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UGSAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

UAbilitySystemComponent* AGSASCActorBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void AGSASCActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
