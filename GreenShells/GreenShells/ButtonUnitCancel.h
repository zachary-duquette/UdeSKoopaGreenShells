#pragma once
#include "Button.h"
class ButtonUnitCancel :
    public Button
{
public:
    ButtonUnitCancel(int sectionOffset, int columnIndex, int rowIndex, int buttonOffset, ButtonState = ButtonState::Disabled);
    ~ButtonUnitCancel();

    void DoAction();

    void LoadTextTexture();
};
