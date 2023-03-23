// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LABPROJECT2DEV_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	virtual void NativeInitializeAnimation() override;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateAnimationProperties();

	UFUNCTION(BlueprintCallable)
	void ResetAttack();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	class APawn* Pawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	class APlayerCharacter* Player;
};
