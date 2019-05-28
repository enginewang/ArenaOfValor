// Ó¢ÐÛµÄ»ù±¾ÒÆ¶¯¡¢°´¼ü°ó¶¨ºÍÉãÏñ»ú¶¨Î»

#include "ArenaOfValorCharacter.h"
#include "ArenaOfValor.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

//////////////////////////////////////////////////////////////////////////
// AArenaOfValorCharacter

AArenaOfValorCharacter::AArenaOfValorCharacter()
{
    // Set size for collision capsule
    //GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    
   
    
    
    
    AttackRangeComp = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRangeComp"));
    
    AttackRangeComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    AttackRangeComp->SetCollisionResponseToAllChannels(ECR_Ignore);
    AttackRangeComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    
    
    
    //FloatHealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("FloatHealthBar"));
    //FloatHealthBar->SetupAttachment(RootComponent);
    //FloatHealthBar->SetCastShadow(false);
    //FloatHealthBar->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
    //AttackRangeComp->SetupAttachment(RootComponent);
    
    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
    
    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;
    // Áª»úºó¼ÇµÃ¸Ä
    MySide = NEUTRAL_SIDE;
    
    AttackDamage = 10.0f;
    AttackCooldown = 2.0f;
    
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

void AArenaOfValorCharacter::BeginPlay() {
    Super::BeginPlay();
     if (AttackRangeComp)
     {
     AttackRangeComp->OnComponentBeginOverlap.AddDynamic(this, &AArenaOfValorCharacter::OnAttackCompBeginOverlap);
         if (GEngine) {
             GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("ifOverlap!")));
         }
     }
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
    //CurPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
    
    //if (GEngine) {
    //    GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Position: %f, %f, %f"), CurPosition.X, CurPosition.Y, CurPosition.Z));
    //}
    
}

FText AArenaOfValorCharacter::setHealthMessage()
{
    FText message = FText::FromString(FString::Printf(TEXT("Health: %d / %d"), (int)CurHealth, (int)MaxHealth));
    return message;
}



void AArenaOfValorCharacter::OnAttackCompBeginOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
   //AttackTimeHandler.Invalidate();
    PerformAttackDamage(OtherActor);
   // GetWorldTimerManager().SetTimer(AttackTimeHandler, this, &AArenaOfValorCharacter::OnRetriggerAttackStrike, AttackCooldown, true);
    if (GEngine) {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Overlap!")));
    }
}

void AArenaOfValorCharacter::OnRetriggerAttackStrike(){
    AttackRangeComp->GetOverlappingActors(ActorsInRadius);
    // É¸Ñ¡¹¥»÷·¶Î§ÄÚµÄµÐÈË
    for (AActor* Actor : ActorsInRadius) {
        AArenaOfValorCharacter* thisActor = Cast<AArenaOfValorCharacter>(Actor);
        if (thisActor) {
            if (thisActor->MySide == 1 - MySide || thisActor->MySide == NEUTRAL_SIDE) {
                //TargetedActors.Push(thisActor);
                // Åöµ½µÚÒ»¸öÖ±½ÓÉËº¦
                PerformAttackDamage(thisActor);
                break;
            }
        }
        UE_LOG(LogTemp, Log, TEXT("%g"), thisActor);
    }
    if (GEngine) {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("AttackStrike!")));
    }
}

void AArenaOfValorCharacter::PerformAttackDamage(AActor* HitActor) {
    //if (LastAttackTime > GetWorld()->GetTimeSeconds() - AttackCooldown) {
      //  return;
    //}
    
    if (HitActor && HitActor != this && isAlive) {
        ACharacter* OtherPawn = Cast<ACharacter>(HitActor);
        
        if (OtherPawn)
        {
         
            LastAttackTime = GetWorld()->GetTimeSeconds();
            
            FPointDamageEvent DmgEvent;
            //DmgEvent.DamageTypeClass = PunchDamageType;
            DmgEvent.Damage = AttackDamage;
            
            HitActor->TakeDamage(DmgEvent.Damage, DmgEvent, GetController(), this);
            //GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("%s attacked"), *HitActor->GetName()));
        }
    }
    if (GEngine) {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("PerformAttack!")));
    }
}

float AArenaOfValorCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
    const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
    if (ActualDamage > 0.f)
    {
        CurHealth -= ActualDamage;
       if (CurHealth <= 0.f)
        {
            SetLifeSpan(0.001f);
        }
    }
    if (GEngine) {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("TakeDamage!")));
    }
    return ActualDamage;
}

void AArenaOfValorCharacter::NotifyActorBeginOverlap(AActor* OtherActor){
    Super::NotifyActorBeginOverlap(OtherActor);
    
    
    AArenaOfValorCharacter* MyCharacter = Cast<AArenaOfValorCharacter>(OtherActor);
    if(MyCharacter){
        MyCharacter->CurHealth-=10;
    }
    if (GEngine) {
        GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Notify!")));
    }
    
}
