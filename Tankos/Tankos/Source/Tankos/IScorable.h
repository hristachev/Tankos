// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStruct.h"
#include "UObject/Interface.h"
#include "IScorable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIScorable : public UInterface
{
	GENERATED_BODY()
};

class TANKOS_API IIScorable
{
	GENERATED_BODY()

public:
	virtual void ScoreAdd(FScoreData ScoreData) = 0;
};
