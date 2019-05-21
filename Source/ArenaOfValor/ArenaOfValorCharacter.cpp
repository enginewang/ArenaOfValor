// 英雄的基本移动、按键绑定和摄像机定位

#include "ArenaOfValorCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ProgressBar.h"
#include "Engine/Engine.h"

//////////////////////////////////////////////////////////////////////////
// AArenaOfValorCharacter

AArenaOfValorCharacter::AArenaOfValorCharacter()
{
	// Set size for collision capsule
	//GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));

	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);


	FloatHealthBar = CreateDefaultSubobject<UProgressBar>(TEXT("FloatHealthBar"));


	// SphereComp->SetupAttachment(RootComponent);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	// 联机后记得改
	MySide = UNDEFINED_SIDE;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AArenaOfValorCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AArenaOfValorCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AArenaOfValorCharacter::MoveRight);


	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AArenaOfValorCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AArenaOfValorCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AArenaOfValorCharacter::OnResetVR);
}




void AArenaOfValorCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AArenaOfValorCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AArenaOfValorCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

/*
void AArenaOfValorCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AArenaOfValorCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
*/

void AArenaOfValorCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AArenaOfValorCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AArenaOfValorCharacter::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);
	CurPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	//if (GEngine) {
	//	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Position: %f, %f, %f"), CurPosition.X, CurPosition.Y, CurPosition.Z));
	//}

}

FText AArenaOfValorCharacter::setHealthMessage()
{
	FText message = FText::FromString(FString::Printf(TEXT("Health: %d / %d"), (int)CurHealth, (int)MaxHealth));
	return message;
}




/*
void AArenaOfValorCharacter::FindEnemies() {
	SphereComp->GetOverlapInfos(ActorsInRadius);

	for (AActor* Actor : ActorsInRadius) {
		;
	}
}

*/

