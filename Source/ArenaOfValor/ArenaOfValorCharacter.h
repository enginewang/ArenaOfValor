// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ArenaOfValorCharacter.generated.h"

UCLASS(config=Game)
class AArenaOfValorCharacter : public ACharacter
{
	GENERATED_BODY()

	/*
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	 */
	
public:
	AArenaOfValorCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	//float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	//float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	
	//void TurnAtRate(float Rate);

	//void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	void BackHome();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	//FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// ÑªÌõbar
	//UPROPERTY(EditAnywhere, Category = "WidgetComponent")
	//	class UWidgetComponent* WidgetComponent;

	// ×ÜÑªÁ¿
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
		int32 TotalHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Transient, Category = "Health")
		int32 CurHealth;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Transient, Category = "Health")
		float HealthProportion;

	virtual void PostInitProperties() override;
};

