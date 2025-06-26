// Copyright 2024 Dan Kestranek.


#include "Characters/GSCharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Characters/GSCharacterBase.h"
#include "GameplayTagContainer.h"

UGSCharacterMovementComponent::UGSCharacterMovementComponent()
{
	SprintSpeedMultiplier = 1.4f;
	ADSSpeedMultiplier = 0.8f;
	KnockedDownSpeedMultiplier = 0.4f;

	KnockedDownTag = FGameplayTag::RequestGameplayTag("State.KnockedDown");
	InteractingTag = FGameplayTag::RequestGameplayTag("State.Interacting");
	InteractingRemovalTag = FGameplayTag::RequestGameplayTag("State.InteractingRemoval");
}

float UGSCharacterMovementComponent::GetMaxSpeed() const
{
	AGSCharacterBase* Owner = Cast<AGSCharacterBase>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() No Owner"), *FString(__FUNCTION__));
		return Super::GetMaxSpeed();
	}

	if (!Owner->IsAlive())
	{
		return 0.0f;
	}

	// Don't move while interacting or being interacted on (revived)
	if (Owner->GetAbilitySystemComponent() && Owner->GetAbilitySystemComponent()->GetTagCount(InteractingTag)
		> Owner->GetAbilitySystemComponent()->GetTagCount(InteractingRemovalTag))
	{
		return 0.0f;
	}

	if (Owner->GetAbilitySystemComponent() && Owner->GetAbilitySystemComponent()->HasMatchingGameplayTag(KnockedDownTag))
	{
		return Owner->GetMoveSpeed() * KnockedDownSpeedMultiplier;
	}

	if (RequestToStartSprinting)
	{
		return Owner->GetMoveSpeed() * SprintSpeedMultiplier;
	}

	if (RequestToStartADS)
	{
		return Owner->GetMoveSpeed() * ADSSpeedMultiplier;
	}

	return Owner->GetMoveSpeed();
}

void UGSCharacterMovementComponent::StartSprinting()
{
	RequestToStartSprinting = true;
}

void UGSCharacterMovementComponent::StopSprinting()
{
	RequestToStartSprinting = false;
}

void UGSCharacterMovementComponent::StartAimDownSights()
{
	RequestToStartADS = true;
}

void UGSCharacterMovementComponent::StopAimDownSights()
{
	RequestToStartADS = false;
}
