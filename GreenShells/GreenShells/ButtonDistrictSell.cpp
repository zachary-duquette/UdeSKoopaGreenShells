#include <iostream>
#include "ButtonDistrictSell.h"
#include "SelectionManager.h"

ButtonDistrictSell::ButtonDistrictSell(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonDistrictSell::~ButtonDistrictSell()
{
}

void ButtonDistrictSell::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonDistrictSell::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\Sell_text.bmp", rend);
        std::cout << "Loading TEXT_BUTTON_SELL_D" << std::endl;
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}