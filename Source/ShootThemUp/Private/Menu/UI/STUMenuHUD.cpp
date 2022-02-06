// Shoot Them Up Game. All Right Reserved.

#include "Menu/UI/STUMenuHUD.h"
#include "Blueprint/UserWidget.h"

void ASTUMenuHUD::BeginPlay() {
    Super::BeginPlay();
     
    if (MenuWidgetClass != nullptr) {
        const auto menu_widget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
        if (menu_widget != nullptr) {
            menu_widget->AddToViewport();
        }
    }
}