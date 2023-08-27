#pragma once
#include "GameplayTagsManager.h"


struct FTitanTestGameplayTags
{
public:
	static const FTitanTestGameplayTags& Get() {return GameplayTags;}
	static FTitanTestGameplayTags GameplayTags;
	static void InitializeGameplayTags();
	static void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);
};
