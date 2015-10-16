#include <iostream>
#include <sstream>
#include <assert.h>
#include <utility>

#include "GameWindow.h"
#include "ServerSession.h"
#include "GameSession.h"
#include "WorldState.h"
#include <assert.h>
#include "Map.h"
#include "TileGround.h"
#include "ClickManager.h"

//Buttons
#include "ButtonGeneralCancel.h"
#include "ButtonDiplomacy.h"
#include "ButtonSkillTree.h"
#include "ButtonSpawnUnit.h"
#include "ButtonConstructDistrict.h"

#include "ButtonUnitAttack.h"
#include "ButtonUnitMove.h"
#include "ButtonUnitHeal.h"
#include "ButtonUnitCancel.h"
#include "ButtonUnitSell.h"
#include "ButtonUnitUpgrade.h"

#include "ButtonDistrictCancel.h"
#include "ButtonDistrictRepair.h"
#include "ButtonDistrictSell.h"
#include "ButtonDistrictUpgrade.h"


GameWindow::GameWindow(ScreenResolution res)
	:m_window(), m_screenSurface(), m_renderer(), m_CurrentScreen(res)
{
	//Initialize SDL
	assert(SDL_Init(SDL_INIT_VIDEO) >= 0 && SDL_GetError());
	
	m_window = SDL_CreateWindow("GreenShells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_CurrentScreen.MAX_WIDTH, m_CurrentScreen.MAX_HEIGHT, SDL_WINDOW_SHOWN);
	assert(m_window != NULL && SDL_GetError());

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	assert(m_renderer != NULL && SDL_GetError());

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    CreateGeneralButtons();
    CreateDistrictButtons();
    CreateUnitButtons();
}

GameWindow::~GameWindow()
{
	Close();
}

void GameWindow::CreateGeneralButtons()
{
    ClickManager::GetInstance().AddButton(new ButtonDiplomacy(0, 1, 1, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonSkillTree(0, 2, 1, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonSpawnUnit(0, 1, 2, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonConstructDistrict(0, 2, 2, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonGeneralCancel(0, 2, 3), LeftMenuPart::GeneralPart);
}

void GameWindow::CreateDistrictButtons()
{
    ClickManager::GetInstance().AddButton(new ButtonDistrictUpgrade(m_CurrentScreen.DISTRICT_MENU_HEIGHT, 1, 1), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonDistrictSell(m_CurrentScreen.DISTRICT_MENU_HEIGHT, 2, 1), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonDistrictRepair(m_CurrentScreen.DISTRICT_MENU_HEIGHT, 1, 2), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonDistrictCancel(m_CurrentScreen.DISTRICT_MENU_HEIGHT, 2, 2), LeftMenuPart::DistrictPart);
}

void GameWindow::CreateUnitButtons()
{
    ClickManager::GetInstance().AddButton(new ButtonUnitAttack(m_CurrentScreen.UNIT_MENU_HEIGHT, 1, 1), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitHeal(m_CurrentScreen.UNIT_MENU_HEIGHT, 2, 1), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitUpgrade(m_CurrentScreen.UNIT_MENU_HEIGHT, 1, 2), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitSell(m_CurrentScreen.UNIT_MENU_HEIGHT, 2, 2), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitMove(m_CurrentScreen.UNIT_MENU_HEIGHT, 1, 3), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitCancel(m_CurrentScreen.UNIT_MENU_HEIGHT, 2, 3), LeftMenuPart::UnitPart);
}

#include "Player.h"
#include "Swordsman.h"
#include "Archer.h"
#include "Farm.h"
#include "CityCenter.h"

void GameWindow::ShowWindow()
{
	bool quit = false;


	// ===================================================
	// TEST DELETE BEFORE PUSH IN MASTER
	// ===================================================
	//GameSession::GetInstance().GetWorldState()->PrepareGame();
	//Player p1 = {};
	//Player p2 = {};
	//GameSession::GetInstance().GetWorldState()->AddPlayer(p1);
	//GameSession::GetInstance().GetWorldState()->AddPlayer(p2);
	//
	//auto p1Tile53 = map->GetTile(Position{ 5,3 });
	//auto p1Tile54 = map->GetTile(Position{ 5,4 });
	//auto p1Tile55 = map->GetTile(Position{ 5,5 });
	//auto p2Tile63 = map->GetTile(Position{ 6,3 });
	//auto p2Tile64 = map->GetTile(Position{ 6,4 });
	//auto p2Tile65 = map->GetTile(Position{ 6,5 });
	//
	//Swordsman* p1Swordsman = new Swordsman(p1.GetPlayerID());
	//Archer* p1Range = new Archer(p1.GetPlayerID());
	//Farm* p1Farm = new Farm(p1.GetPlayerID());
	//CityCenter* p1CityCenter = new CityCenter(p1.GetPlayerID());
	//
	//Swordsman* p2Swordsman = new Swordsman(p2.GetPlayerID());
	//Archer* p2Range = new Archer(p2.GetPlayerID());
	//Farm* p2Farm = new Farm(p2.GetPlayerID());
	//CityCenter* p2CityCenter = new CityCenter(p2.GetPlayerID());
	//
	//p1Tile53->SetUnit(p1Range);
	//p1Tile54->SetDistrict(p1Farm);
	//p1Tile55->SetUnit(p1Swordsman);
	//p1Tile55->SetDistrict(p1CityCenter);
	//
	//p2Tile63->SetUnit(p2Range);
	//p2Tile65->SetUnit(p2Swordsman);
	//p2Tile64->SetDistrict(p2CityCenter);
	//p2Tile65->SetDistrict(p2Farm);
	//
	//map->Attack(p1.GetPlayerID(), Position(5, 5), Position(6, 4));
	//map->Attack(p1.GetPlayerID(), Position(5, 5), Position(6, 4));
	//map->Attack(p1.GetPlayerID(), Position(5, 5), Position(6, 4));
	//map->Attack(p1.GetPlayerID(), Position(5, 5), Position(6, 4));
	//map->Attack(p1.GetPlayerID(), Position(5, 3), Position(6, 3));

	// ===================================================

	while (!quit)
	{
		SDL_Event e;

		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{
				std::cout << "clicked at X: " << e.button.x << " Y: " << e.button.y << std::endl;
				if (IsClickInMap(e.button.x, e.button.y))
				{
					int posX = (e.button.x - m_CurrentScreen.HUD_WIDTH) / m_CurrentScreen.TILE_SIZE;
					int posY = (e.button.y - m_CurrentScreen.HUD_HEIGHT) / m_CurrentScreen.TILE_SIZE;

					ClickManager::GetInstance().ManageMapClick(Position(posX,posY));
				}
				else if (IsClickInLeftMenu(e.button.x, e.button.y))
				{
					ClickManager::GetInstance().ManageLeftMenuClick(e.button.x, e.button.y);
				}
				else
				{
					ClickManager::GetInstance().ManageTopMenuClick(e.button.x, e.button.y);
				}
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(m_renderer, 32, 32, 32, 0);
		SDL_RenderClear(m_renderer);

        //Render UI
        //Render Buttons
        const std::vector<Button*> generalButtons = ClickManager::GetInstance().GetGeneralButtons();
        for (Button* button : generalButtons)
        {
            int x = button->GetLeftX();
            int y = button->GetTopY();
            int width = button->GetWidth();
            int height = button->GetHeight();
            SDL_Rect renderQuad = { x, y, width, height };

            Texture* buttonTexture = button->GetButtonTexture();
            Texture * textTexture = button->GetTextTexture();

            SDL_RenderCopy(m_renderer, buttonTexture->GetTexture(), NULL, &renderQuad);
            SDL_RenderCopy(m_renderer, textTexture->GetTexture(), NULL, &renderQuad);
        }

        const std::vector<Button*> districtButtons = ClickManager::GetInstance().GetDistrictButtons();
        for (Button* button : districtButtons)
        {
            int x = button->GetLeftX();
            int y = button->GetTopY();
            int width = button->GetWidth();
            int height = button->GetHeight();
            SDL_Rect renderQuad = { x, y, width, height };

            Texture* buttonTexture = button->GetButtonTexture();
            Texture * textTexture = button->GetTextTexture();

            SDL_RenderCopy(m_renderer, buttonTexture->GetTexture(), NULL, &renderQuad);
            SDL_RenderCopy(m_renderer, textTexture->GetTexture(), NULL, &renderQuad);
        }

		const std::vector<Button*> unitButtons = ClickManager::GetInstance().GetUnitButtons();
		for (Button* button : unitButtons)
		{
			int x = button->GetLeftX();
			int y = button->GetTopY();
			int width = button->GetWidth();
			int height = button->GetHeight();
			SDL_Rect renderQuad = { x, y, width, height };

            Texture* buttonTexture = button->GetButtonTexture();
            Texture * textTexture = button->GetTextTexture();

			SDL_RenderCopy(m_renderer, buttonTexture->GetTexture(), NULL, &renderQuad);
            SDL_RenderCopy(m_renderer, textTexture->GetTexture(), NULL, &renderQuad);
		}

		//Render Map
		Map map = GameSession::GetInstance().GetWorldState()->GetMapCopy();
		for (int i = 0; i <= m_CurrentScreen.NUM_TILE_HEIGHT; ++i)
		{
			for (int j = 0; j <= m_CurrentScreen.NUM_TILE_WIDTH; ++j)
			{
				Texture* tileTexture = map.GetTile(Position(i, j))->GetTexture();

				//Position the tile on the screen
				int x = m_CurrentScreen.HUD_WIDTH + (j * m_CurrentScreen.TILE_SIZE);
				int y = m_CurrentScreen.HUD_HEIGHT + (i * m_CurrentScreen.TILE_SIZE);
				SDL_Rect renderQuad = { x, y, tileTexture->GetWidth(), tileTexture->GetHeight() };

				//Render the tile
				SDL_RenderCopy(m_renderer, tileTexture->GetTexture(), NULL, &renderQuad);

				//TODO Render the district + unit on the tile
			}
		}
		//Draw screen
		SDL_RenderPresent(m_renderer);
	}
	Close();
}

SDL_Renderer * GameWindow::GetRenderer()
{
	return m_renderer;
}

void GameWindow::Close()
{
	//Destroy window    
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	m_window = NULL;
	m_renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

bool GameWindow::IsClickInLeftMenu(const int & x, const int & y)
{
	return x < m_CurrentScreen.HUD_WIDTH && 0 < y;
}

bool GameWindow::IsClickInMap(const int& x, const int& y)
{
	return m_CurrentScreen.HUD_WIDTH < x && x < m_CurrentScreen.MAX_WIDTH && m_CurrentScreen.HUD_HEIGHT < y && y < m_CurrentScreen.MAX_HEIGHT;
}
