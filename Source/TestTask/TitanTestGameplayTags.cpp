#include "TitanTestGameplayTags.h"

FTitanTestGameplayTags FTitanTestGameplayTags::GameplayTags;

void FTitanTestGameplayTags::InitializeGameplayTags()
{
	
}

void FTitanTestGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), TagComment);
}
