#include <iostream>
#include "ButtonSpawnUnit.h"
#include "SelectionManager.h"

ButtonSpawnUnit::ButtonSpawnUnit(int sectionOffset, int columnIndex, int rowIndex, ButtonState state)
    :Button(sectionOffset, columnIndex, rowIndex, state)
{
}

ButtonSpawnUnit::~ButtonSpawnUnit()
{
}

void ButtonSpawnUnit::DoAction()
{
    //TODO NOT IMPLEMENTED
}

void ButtonSpawnUnit::LoadTextTexture()
{
    try
    {
        m_textTexture.LoadFromFile("..\\Sprite\\Button\\SpawnUnit_text.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}