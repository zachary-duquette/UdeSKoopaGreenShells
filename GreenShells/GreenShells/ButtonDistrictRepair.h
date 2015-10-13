#pragma once
#include "Button.h"
class ButtonDistrictRepair :
    public Button
{
public:
    ButtonDistrictRepair(int sectionOffset, int columnIndex, int rowIndex, ButtonState = ButtonState::Disabled);
    ~ButtonDistrictRepair();

    void DoAction();

    void LoadTextTexture();
};