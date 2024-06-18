#include "DamageWidget.h"
#include "Components/Image.h"
#include "Proyecto3PlayerController.h"
#include "ProyectoIntermedio3Character.h"

void UDamageWidget::NativeConstruct()
{
	DamageImage->SetVisibility(ESlateVisibility::Hidden);
	DamageImage->SetOpacity(0.0f);

	auto* world = GetWorld();

	if (!world)
		return;

	auto controller = Cast<AProyecto3PlayerController>(world->GetFirstPlayerController());

	if (!controller)
		return;

	auto* player = Cast<AProyectoIntermedio3Character>(controller->GetPawn());

	if (!player || !player->OxygenComponent)
		return;

	player->OnTakeDamage.AddDynamic(this, &UDamageWidget::ShowDamageEffect);
}

void UDamageWidget::ShowDamageEffect()
{
	DamageImage->SetVisibility(ESlateVisibility::Visible);

	FadeTimer = 0.0f;

	GetWorld()->GetTimerManager().SetTimer(DamageTimer, this, &UDamageWidget::UpdateFadeEffect, 0.01f, true);
}

void UDamageWidget::HideDamageEffect()
{
	GetWorld()->GetTimerManager().ClearTimer(DamageTimer);

	DamageImage->SetVisibility(ESlateVisibility::Hidden);

	DamageImage->SetOpacity(0.0f);
}

void UDamageWidget::UpdateFadeEffect()
{
	FadeTimer += 0.01f;
	float Alpha = FMath::Lerp(1.f, 0.f, FadeTimer / FadeDuration);
	DamageImage->SetOpacity(Alpha);

	if (FadeTimer >= FadeDuration)
	{
		HideDamageEffect();
	}
}