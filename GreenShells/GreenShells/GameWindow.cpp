#include <iostream>
#include <sstream>
#include <assert.h>
#include <utility>
#include <assert.h>

#include "UnitBase.h"
#include "DistrictBase.h"
#include "GameWindow.h"
#include "ServerSession.h"
#include "GameSession.h"
#include "WorldState.h"
#include "Map.h"
#include "TileGround.h"
#include "ClickManager.h"
#include "SelectionManager.h"
#include "Player.h"

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

// Unit
#include "UnitArcher.h"
#include "UnitSwordsman.h"
#include "UnitSettler.h"

// District 
#include "DistrictFarm.h"
#include "DistrictCityCenter.h"


GameWindow::GameWindow(ScreenResolution res)
	:m_window(), m_screenSurface(), m_renderer(), m_CurrentScreen(res), m_currentLeftmostColumn(0), m_currentLowestRow(0), m_currentlyScrolling(false), m_foodTexture(), m_overlayTexture(), m_scienceTexture(), m_weaponTexture()
{ 
//Initialize SDL                                                                                                                            
	assert(SDL_Init(SDL_INIT_VIDEO) >= 0 && SDL_GetError());
	assert(TTF_Init() >= 0 && TTF_GetError());

	auto windowType = m_CurrentScreen.FULLSCREEN ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_SHOWN;
	m_window = SDL_CreateWindow("GreenShells", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_CurrentScreen.MAX_WIDTH, m_CurrentScreen.MAX_HEIGHT, windowType);
	assert(m_window != NULL && SDL_GetError());

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	assert(m_renderer != NULL && SDL_GetError());

	SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    m_overlayTexture = new Texture();
    m_overlayTexture->LoadFromFile("..\\Sprite\\overlay.bmp", m_renderer);

	CreateGeneralButtons();
	CreateDistrictButtons();
	CreateUnitButtons();
	CreateRessourcesTextures();
}

GameWindow::~GameWindow()
{
	Close();
}

void GameWindow::CreateGeneralButtons()
{
    ClickManager::GetInstance().AddButton(new ButtonDiplomacy(0, 1, 1, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonSkillTree(0, 2, 1, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonSpawnUnit(0, 1, 2, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonConstructDistrict(0, 2, 2, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET, ButtonState::Unpressed), LeftMenuPart::GeneralPart);
    ClickManager::GetInstance().AddButton(new ButtonGeneralCancel(0, 2, 3, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::GeneralPart);
}

void GameWindow::CreateDistrictButtons()
{
    ClickManager::GetInstance().AddButton(new ButtonDistrictUpgrade(m_CurrentScreen.DISTRICT_MENU_BUTTON_HEIGHT, 1, 1, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonDistrictSell(m_CurrentScreen.DISTRICT_MENU_BUTTON_HEIGHT, 2, 1, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonDistrictRepair(m_CurrentScreen.DISTRICT_MENU_BUTTON_HEIGHT, 1, 2, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::DistrictPart);
    ClickManager::GetInstance().AddButton(new ButtonDistrictCancel(m_CurrentScreen.DISTRICT_MENU_BUTTON_HEIGHT, 2, 2, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::DistrictPart);
}

void GameWindow::CreateUnitButtons()
{
    ClickManager::GetInstance().AddButton(new ButtonUnitAttack(m_CurrentScreen.UNIT_MENU_BUTTON_HEIGHT, 1, 1, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitHeal(m_CurrentScreen.UNIT_MENU_BUTTON_HEIGHT, 2, 1, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitUpgrade(m_CurrentScreen.UNIT_MENU_BUTTON_HEIGHT, 1, 2, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitSell(m_CurrentScreen.UNIT_MENU_BUTTON_HEIGHT, 2, 2, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitMove(m_CurrentScreen.UNIT_MENU_BUTTON_HEIGHT, 1, 3, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::UnitPart);
    ClickManager::GetInstance().AddButton(new ButtonUnitCancel(m_CurrentScreen.UNIT_MENU_BUTTON_HEIGHT, 2, 3, m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET, m_CurrentScreen.BUTTON_VERTICAL_OFFSET), LeftMenuPart::UnitPart);
}

void GameWindow::CreateRessourcesTextures()
{
	m_ressourcesFont = TTF_OpenFont("..\\Fonts\\roboto\\Roboto-Thin.ttf", 16);
	assert(m_ressourcesFont != NULL && TTF_GetError());

	m_foodTexture = new Texture();
	m_weaponTexture = new Texture();
	m_scienceTexture = new Texture();
	try
	{
		// Do not remove the renderer from this call otherwise the Load from file will call
		// GetInstance of game window wich will lead us back here and.... you know the rest INFINITY LOOP
		m_foodTexture->LoadFromFile("..\\Sprite\\Resources\\64x64\\food.bmp", m_renderer);

		m_weaponTexture->LoadFromFile("..\\Sprite\\Resources\\64x64\\weapons.bmp", m_renderer);

		m_scienceTexture->LoadFromFile("..\\Sprite\\Resources\\64x64\\science.bmp", m_renderer);
	}
	catch (std::exception e)
	{
		std::string msg{ e.what() };
		std::cout << msg << std::endl;
	}
	
	

}

void GameWindow::ShowWindow()
{
	bool quit = false;
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
				std::cout << "clicked at Column: " << e.button.x << " Row: " << e.button.y << std::endl;
				if (SDL_GetWindowID(m_window) == e.button.windowID && !IsGameWindowInBackground())
				{
					if (IsClickInMap(e.button.x, e.button.y))
					{
						int posCol = ((e.button.x - m_CurrentScreen.HUD_WIDTH) / m_CurrentScreen.TILE_SIZE) + m_currentLeftmostColumn;
						posCol %= (Map::COLUMNS -1);

						int posRow = ((e.button.y - m_CurrentScreen.HUD_HEIGHT) / m_CurrentScreen.TILE_SIZE) + m_currentLowestRow;
						posRow %= (Map::ROWS -1);

						ClickManager::GetInstance().ManageMapClick(Position(posCol, posRow));
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
				else 
				{
					PopUpWindow* popUpToRemove = nullptr;
					for (PopUpWindow* popUp : m_activePopUpWindow)
					{
						SDL_RaiseWindow(popUp->GetWindow());
						if (SDL_GetWindowID(popUp->GetWindow()) == e.button.windowID)
						{
							if (popUp->handleEvent(e))
							{
								popUpToRemove = popUp;
							}
							break;
						}
					}

					if (popUpToRemove != nullptr)
					{
						//Remove it from the vector
						m_activePopUpWindow.erase(std::remove(m_activePopUpWindow.begin(), m_activePopUpWindow.end(), popUpToRemove), m_activePopUpWindow.end());
						popUpToRemove->Close();
					}
				}
			}
            else if (e.type == SDL_KEYDOWN && !IsGameWindowInBackground())
			{
				switch (e.key.keysym.sym)
				{
				case (SDLK_UP) :
					if (m_currentLowestRow > 0)
                    {
						m_currentLowestRow--;
                    }
                    else
                    {
                        m_currentLowestRow = Map::ROWS - 1;
                    }
					break;
				case (SDLK_LEFT) :
					if (m_currentLeftmostColumn > 0)
                    {
						m_currentLeftmostColumn--;
                    }
                    else
                    {
                        m_currentLeftmostColumn = Map::COLUMNS - 1;
                    }
					break;
				case (SDLK_RIGHT) :
                        m_currentLeftmostColumn = (m_currentLeftmostColumn + 1) % (Map::COLUMNS -1);
					break;
				case (SDLK_DOWN) :
                        m_currentLowestRow = (m_currentLowestRow + 1) % (Map::ROWS - 1);
					break;
				}
			}
            /*
            TODO Remove comment when the speed for scroll is reduced

			else if (e.type == SDL_MOUSEMOTION)
			{
				m_currentlyScrolling = e.button.x > m_CurrentScreen.RIGHT_SCROLL_POSITION
					|| (e.button.x < m_CurrentScreen.LEFT_SCROLL_POSITION && e.button.x > m_CurrentScreen.HUD_WIDTH)
					|| e.button.y > m_CurrentScreen.DOWN_SCROLL_POSITION
					|| (e.button.y < m_CurrentScreen.UP_SCROLL_POSITION && e.button.y > m_CurrentScreen.HUD_HEIGHT);
			}
            */
		}

        /*
        TODO Remove comment when the speed for scroll is reduced
		//mouse scroll
        if (m_currentlyScrolling && !IsGameWindowInBackground())
		{
			int mouseX = 0;
			int mouseY = 0;
			SDL_GetMouseState(&mouseX, &mouseY);

			if (m_currentLeftmostColumn < Map::COLUMNS - m_CurrentScreen.NUM_TILE_WIDTH - 1 && mouseX > m_CurrentScreen.RIGHT_SCROLL_POSITION)
				m_currentLeftmostColumn++;
			else if (m_currentLeftmostColumn > 0 && mouseX < m_CurrentScreen.LEFT_SCROLL_POSITION && e.button.x > m_CurrentScreen.HUD_WIDTH)
				m_currentLeftmostColumn--;

			if (m_currentLowestRow < Map::ROWS - m_CurrentScreen.NUM_TILE_HEIGHT - 1 && mouseY > m_CurrentScreen.DOWN_SCROLL_POSITION)
				m_currentLowestRow++;
			else if (m_currentLowestRow > 0 && mouseY < m_CurrentScreen.UP_SCROLL_POSITION && mouseY > m_CurrentScreen.HUD_HEIGHT)
				m_currentLowestRow--;


		}
        */

		//Clear screen
		SDL_SetRenderDrawColor(m_renderer, 32, 32, 32, 0);
		SDL_RenderClear(m_renderer);

		//Render UI
		//Render ressources and turns
		{
			SDL_Color textColor = { 255, 255, 255 };

			Player currentPlayer = GameSession::GetInstance().GetWorldState()->GetPlayer(GameSession::GetInstance().GetCurrentPlayerID());

			/************
			    FOOD
			*************/
			int iconTextSpacing = 5;
			int x = m_CurrentScreen.HUD_WIDTH;
			int yIcon = 10;
			int widthIcon = 64;
			int heightIcon = 64;
			int widthText = 0;
			int heightText = 0;
			int yText = 0;

			SDL_Rect renderQuadFood = { x, yIcon, widthIcon, heightIcon };
			SDL_RenderCopy(m_renderer, m_foodTexture->GetTexture(), NULL, &renderQuadFood);

			SDL_Surface *foodSurf = TTF_RenderText_Solid(m_ressourcesFont,std::to_string(currentPlayer.GetFood()).c_str() , textColor);
			assert(foodSurf != NULL && TTF_GetError());

			SDL_Texture* foodTextTexture = SDL_CreateTextureFromSurface(m_renderer, foodSurf);
			assert(foodTextTexture != NULL && TTF_GetError());

			x += widthIcon + iconTextSpacing;
			widthText = foodSurf->w;
			heightText = foodSurf->h;
			yText = yIcon + heightIcon - heightText;

			SDL_Rect renderQuadFoodValue = { x, yText, widthText, heightText};
			SDL_RenderCopy(m_renderer, foodTextTexture, NULL, &renderQuadFoodValue);


			/************
			   WEAPON
			*************/
			x += widthIcon + widthText + iconTextSpacing;

			SDL_Rect renderQuadWeapon = { x, yIcon, widthIcon, heightIcon };
			SDL_RenderCopy(m_renderer, m_weaponTexture->GetTexture(), NULL, &renderQuadWeapon);

			SDL_Surface *weaponSurf = TTF_RenderText_Solid(m_ressourcesFont, std::to_string(currentPlayer.GetWeapon()).c_str(), textColor);
			assert(weaponSurf != NULL && TTF_GetError());

			SDL_Texture* weaponTextTexture = SDL_CreateTextureFromSurface(m_renderer, weaponSurf);
			assert(weaponTextTexture != NULL && TTF_GetError());

			x += widthIcon + iconTextSpacing;
			widthText = weaponSurf->w;
			heightText = weaponSurf->h;

			SDL_Rect renderQuadWeaponValue = { x, yText, widthText, heightText };
			SDL_RenderCopy(m_renderer, weaponTextTexture, NULL, &renderQuadWeaponValue);

			/************
			   SCIENCE
			*************/
			x += widthIcon + widthText + iconTextSpacing;

			SDL_Rect renderQuadScience = { x, yIcon, widthIcon, heightIcon };
			SDL_RenderCopy(m_renderer, m_scienceTexture->GetTexture(), NULL, &renderQuadScience);

			SDL_Surface *scienceSurf = TTF_RenderText_Solid(m_ressourcesFont, std::to_string(currentPlayer.GetScience()).c_str(), textColor);
			assert(scienceSurf != NULL && TTF_GetError());

			SDL_Texture* scienceTextTexture = SDL_CreateTextureFromSurface(m_renderer, scienceSurf);
			assert(scienceTextTexture != NULL && TTF_GetError());

			x += widthIcon + iconTextSpacing;
			widthText = scienceSurf->w;
			heightText = scienceSurf->h;

			SDL_Rect renderQuadScienceValue = { x, yText, widthText, heightText };
			SDL_RenderCopy(m_renderer, scienceTextTexture, NULL, &renderQuadScienceValue);

			/************
			    TURN
			*************/
			x += widthIcon + widthText + iconTextSpacing;
			std::string turnText = "Turn : ";
			turnText.append(std::to_string(GameSession::GetInstance().GetWorldState()->GetCurrentTurn()));

			SDL_Surface* turnSurf = TTF_RenderText_Solid(m_ressourcesFont, turnText.c_str(), textColor);
			assert(turnSurf != NULL && TTF_GetError());

			SDL_Texture* turnTextTexture = SDL_CreateTextureFromSurface(m_renderer, turnSurf);
			assert(turnTextTexture != NULL && TTF_GetError());

			widthText = turnSurf->w;
			heightText = turnSurf->h;

			SDL_Rect renderQuadTurnValue = { x, yText, widthText, heightText };
			SDL_RenderCopy(m_renderer, turnTextTexture, NULL, &renderQuadTurnValue);

		}

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

        //Render Selected district
        {
            Texture* selectedDistrictTexture = SelectionManager::GetInstance().GetSelectedDistrict()->GetTexture();
            int xPos = m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET;
            int yPos = m_CurrentScreen.SELECTED_DISTRICT_HEIGHT;
            SDL_Rect renderQuad = { xPos, yPos, selectedDistrictTexture->GetWidth(), selectedDistrictTexture->GetHeight() };

            //Remove Color and render
            selectedDistrictTexture->SetColor(255, 255, 255);
            SDL_RenderCopy(m_renderer, selectedDistrictTexture->GetTexture(), NULL, &renderQuad);
        }

        //Render Selected unit 
        {
            Texture* selectedUnitTexture = SelectionManager::GetInstance().GetSelectedUnit()->GetTexture();
            int xPos = m_CurrentScreen.BUTTON_HORIZONTAL_OFFSET;
            int yPos = m_CurrentScreen.SELECTED_UNIT_HEIGHT;
            SDL_Rect renderQuad = { xPos, yPos, selectedUnitTexture->GetWidth(), selectedUnitTexture->GetHeight() };

            //Remove Color and render
            selectedUnitTexture->SetColor(255, 255, 255);
            SDL_RenderCopy(m_renderer, selectedUnitTexture->GetTexture(), NULL, &renderQuad);
        }

		//Render Map
		Map map = GameSession::GetInstance().GetWorldState()->GetMapCopy();

        //Set overlay visible to true
        std::vector<Position> overlayTiles = SelectionManager::GetInstance().GetOverlayTiles();
        for (Position pos : overlayTiles)
        {
            map.GetTile(pos)->SetOverlayVisible(true);
        }

        int rowIndex = m_currentLowestRow;
        for (int row = 0; row <= m_CurrentScreen.NUM_TILE_HEIGHT; ++row)
		{
            int columnIndex = m_currentLeftmostColumn;
            for (int column = 0; column <= m_CurrentScreen.NUM_TILE_WIDTH; ++column)
			{
                TileBase* tile = map.GetTile(Position(columnIndex, rowIndex));
				Texture* tileTexture = tile->GetTexture();

				//Position the tile on the screen
                int xPos = m_CurrentScreen.HUD_WIDTH + (column * m_CurrentScreen.TILE_SIZE);
                int yPos = m_CurrentScreen.HUD_HEIGHT + (row * m_CurrentScreen.TILE_SIZE);
				SDL_Rect renderQuad = { xPos, yPos, tileTexture->GetWidth(), tileTexture->GetHeight() };

				//Render the tile
				SDL_RenderCopy(m_renderer, tileTexture->GetTexture(), NULL, &renderQuad);

                //Render the district
				DistrictBase* district = tile->GetDistrict();
				if (district)
				{
					Texture* districtTexture = district->GetTexture();
                    districtTexture->SetColor(PLAYER_COLORS[district->GetOwnerID()]);
					SDL_RenderCopy(m_renderer, districtTexture->GetTexture(), NULL, &renderQuad);
				}

                //Render the unit
				UnitBase* unit = tile->GetUnit();
				if (unit)
				{
					Texture* unitTexture = unit->GetTexture();
                    unitTexture->SetColor(PLAYER_COLORS[unit->GetOwnerID()]);
					SDL_RenderCopy(m_renderer, unitTexture->GetTexture(), NULL, &renderQuad);
				}

                //Render the overlay
                if (tile->GetOverlayVisible())
                {
                    SDL_RenderCopy(m_renderer, m_overlayTexture->GetTexture(), NULL, &renderQuad);
                }

				columnIndex = (columnIndex + 1) % (Map::COLUMNS);

			}
			rowIndex = (rowIndex + 1) % (Map::ROWS);

		}
		//Draw screen
		SDL_RenderPresent(m_renderer);

		//Render the different popUps
		for (PopUpWindow* popUp : m_activePopUpWindow)
		{
			popUp->ShowWindow(m_renderer);
		}
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
	TTF_Quit();
	SDL_Quit();
}

bool GameWindow::IsClickInLeftMenu(const int & x, const int & y)
{
	return x < m_CurrentScreen.HUD_WIDTH && 0 < y;
}

void GameWindow::AddPopUpWindow(PopUpWindow * window)
{
	m_activePopUpWindow.emplace_back(window);
}

bool GameWindow::IsGameWindowInBackground()
{
	return m_activePopUpWindow.size() > 0;
}

bool GameWindow::IsClickInMap(const int& x, const int& y)
{
	return m_CurrentScreen.HUD_WIDTH < x && x < m_CurrentScreen.MAX_WIDTH && m_CurrentScreen.HUD_HEIGHT < y && y < m_CurrentScreen.MAX_HEIGHT;
}
