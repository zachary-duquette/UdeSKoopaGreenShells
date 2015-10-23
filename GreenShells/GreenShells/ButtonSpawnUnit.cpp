#include <iostream>
#include "ButtonSpawnUnit.h"
#include "SelectionManager.h"

ButtonSpawnUnit::ButtonSpawnUnit(int sectionOffset, int columnIndex, int rowIndex, int buttonHOffset, int buttonVOffset, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, buttonHOffset, buttonVOffset, state)
{
}

ButtonSpawnUnit::~ButtonSpawnUnit()
{
}

void ButtonSpawnUnit::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonSpawnUnit::LoadTextTexture(SDL_Renderer* rend)
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\SpawnUnit_text.bmp", rend);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}
