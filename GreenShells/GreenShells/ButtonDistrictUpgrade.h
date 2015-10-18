#pragma once
#include "Button.h"
class ButtonDistrictUpgrade :
    public Button
{
public:
    ButtonDistrictUpgrade(int sectionOffset, int columnIndex, int rowIndex, ButtonState = ButtonState::Disabled);
    ~ButtonDistrictUpgrade();

    void DoAction();

    void LoadTextTexture();
};