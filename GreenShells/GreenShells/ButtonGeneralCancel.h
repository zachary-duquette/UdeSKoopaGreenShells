#pragma once
#include "Button.h"
class ButtonGeneralCancel :
    public Button
{
public:
    ButtonGeneralCancel(int sectionOffset, int columnIndex, int rowIndex, int buttonOffset, ButtonState = ButtonState::Disabled);
    ~ButtonGeneralCancel();

    void DoAction();

    void LoadTextTexture();
};