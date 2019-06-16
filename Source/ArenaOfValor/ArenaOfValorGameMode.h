// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
// 没用到这个GameMode，游戏的GameMode在Blueprint中实现的

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArenaOfValorGameMode.generated.h"

UCLASS(minimalapi)
class AArenaOfValorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AArenaOfValorGameMode();
};



