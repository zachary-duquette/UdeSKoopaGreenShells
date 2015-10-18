#pragma once
#include "Button.h"
class ButtonDistrictSell :
    public Button
{
public:
    ButtonDistrictSell(int sectionOffset, int columnIndex, int rowIndex, ButtonState = ButtonState::Disabled);
    ~ButtonDistrictSell();

    void DoAction();

    void LoadTextTexture();
};