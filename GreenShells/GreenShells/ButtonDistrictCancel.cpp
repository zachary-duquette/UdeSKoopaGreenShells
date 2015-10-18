#include <iostream>
#include "ButtonDistrictCancel.h"
#include "SelectionManager.h"

ButtonDistrictCancel::ButtonDistrictCancel(int sectionOffset, int columnIndex, int rowIndex, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, state)
{
}

ButtonDistrictCancel::~ButtonDistrictCancel()
{
}

void ButtonDistrictCancel::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonDistrictCancel::LoadTextTexture()
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