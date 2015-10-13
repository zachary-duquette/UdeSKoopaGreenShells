#include <iostream>
#include "ButtonConstructDistrict.h"
#include "SelectionManager.h"

ButtonConstructDistrict::ButtonConstructDistrict(int sectionOffset, int columnIndex, int rowIndex, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, state)
{
}

ButtonConstructDistrict::~ButtonConstructDistrict()
{
}

void ButtonConstructDistrict::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonConstructDistrict::LoadTextTexture()
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Upgrade_text.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}