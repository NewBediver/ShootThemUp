// Shoot Them Up Game. All Right Reserved.

#include "Menu/UI/STUMenuHUD.h"
#include "UI/STUBaseWidget.h"

void ASTUMenuHUD::BeginPlay() {
    Super::BeginPlay();
     
    if (MenuWidgetClass != nullptr) {
        const auto menu_widget = CreateWidget<USTUBaseWidget>(GetWorld(), MenuWidgetClass);
        if (menu_widget != nullptr) {
            menu_widget->AddToViewport();
            menu_widget->Show();
        }
    }
}