#include "ButtonNextTurn.h"
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "GameSession.h"
#include "SelectionManager.h"
#include "Player.h"

ButtonNextTurn::ButtonNextTurn(int posX, int posY, int width, int height, ButtonState state)
    :Button(posX, posY, width, height, state)
{
}

ButtonNextTurn::~ButtonNextTurn()
{
}

void ButtonNextTurn::DoAction()
{
    GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID())->SetPlayerReadyForNextTurn();
    SelectionManager::GetInstance().UpdateButtonState();
}

void ButtonNextTurn::LoadTextTexture(SDL_Renderer * rend)
{
    try
    {
        TTF_Font* font = TTF_OpenFont("..\\Fonts\\roboto\\Roboto-BlackItalic.ttf", 30);
        m_textTexture.CreateFromText("Next Turn", font);
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}