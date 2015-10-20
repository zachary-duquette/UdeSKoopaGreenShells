#include <iostream>
#include "ButtonUnitCancel.h"
#include "SelectionManager.h"

ButtonUnitCancel::ButtonUnitCancel(int sectionOffset, int columnIndex, int rowIndex, int buttonOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonOffset, state)
{
}

ButtonUnitCancel::~ButtonUnitCancel()
{
}

void ButtonUnitCancel::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonUnitCancel::LoadTextTexture()
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Cancel_text.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
