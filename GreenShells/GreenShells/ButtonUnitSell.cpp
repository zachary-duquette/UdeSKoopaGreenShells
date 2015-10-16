#include <iostream>
#include "ButtonUnitSell.h"
#include "SelectionManager.h"

ButtonUnitSell::ButtonUnitSell(int sectionOffset, int columnIndex, int rowIndex, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, state)
{
}

ButtonUnitSell::~ButtonUnitSell()
{
}

void ButtonUnitSell::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonUnitSell::LoadTextTexture()
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Sell_text.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
