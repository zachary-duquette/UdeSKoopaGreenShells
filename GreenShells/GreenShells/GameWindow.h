#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <thread>
#include "GameSession.h"
#include "Texture.h"
#include "PopUpWindow.h"

//////////////////////////////////
//Screen Resolution
/////////////////////////////////
struct ScreenResolution
{
    const int TILE_SIZE = 65;
    const int SELECTED_SPRITES_SIZE = 70;
    const int BUTTON_HORIZONTAL_OFFSET = 25;

    int HUD_WIDTH;
    int HUD_HEIGHT;
    int MAX_WIDTH;
    int MAX_HEIGHT;
    int MAP_HEIGHT;
    int MAP_WIDTH;
    int SELECTED_UNIT_HEIGHT;
    int SELECTED_DISTRICT_HEIGHT;
    int BUTTON_VERTICAL_OFFSET;
    int NUM_TILE_HEIGHT;
    int NUM_TILE_WIDTH;
    int DISTRICT_MENU_BUTTON_HEIGHT;
    int UNIT_MENU_BUTTON_HEIGHT;
    int DOWN_SCROLL_POSITION;
    int UP_SCROLL_POSITION;
    int RIGHT_SCROLL_POSITION;
    int LEFT_SCROLL_POSITION;

    ScreenResolution(int maxW, int maxH, int mapW, int mapH, int hudW, int hudH, int vOffset, int DistrictH, int UnitH)
        :MAX_WIDTH(maxW)
        , MAX_HEIGHT(maxH)
        , MAP_WIDTH(mapW)
        , MAP_HEIGHT(mapH)
        , SELECTED_UNIT_HEIGHT(UnitH - SELECTED_SPRITES_SIZE)
        , SELECTED_DISTRICT_HEIGHT(DistrictH - SELECTED_SPRITES_SIZE)
        , HUD_WIDTH(hudW)
        , HUD_HEIGHT(hudH)
        , BUTTON_VERTICAL_OFFSET(vOffset)
        , NUM_TILE_WIDTH((mapW / TILE_SIZE) - 1)
        , NUM_TILE_HEIGHT((mapH / TILE_SIZE) - 1)
        , DISTRICT_MENU_BUTTON_HEIGHT(DistrictH)
        , UNIT_MENU_BUTTON_HEIGHT(UnitH)
        , DOWN_SCROLL_POSITION(maxH - 15)
        , RIGHT_SCROLL_POSITION(maxW - 15)
        , LEFT_SCROLL_POSITION(hudW + 15)
        , UP_SCROLL_POSITION(hudH + 15)
    {}
};
static ScreenResolution RES_800_600{ 800,600,520,520,280,80,5,240,425 };
static ScreenResolution RES_1280_720{ 1280,720,975,650,305,70,12,292,498 };
static ScreenResolution RES_1600_900{ 1600,900,1300,780,300,120,25,362,650 };
static ScreenResolution RES_1600_1024{ 1600,1024,1300,910,300,114,35,410,735 };
static ScreenResolution RES_1920_1080{ 1920,1080,1625,975,295,105,38,319,664 };

class GameWindow
{
private:

    ScreenResolution m_CurrentScreen;

    SDL_Window* m_window;
    SDL_Surface* m_screenSurface;
    SDL_Renderer* m_renderer;
    int m_currentLeftmostX;
    int m_currentLowestY;
    bool m_currentlyScrolling;

	std::vector<PopUpWindow*> m_activePopUpWindow;

	TTF_Font* m_ressourcesFont;
	Texture* m_foodTexture;
	Texture* m_weaponTexture;
	Texture* m_scienceTexture;

    const Color PLAYER_COLORS[8] =
    {
        Color{ 255,102,102 },
        Color{ 255,255,102 },
        Color{ 102,255,102 },
        Color{ 102,255,255 },
        Color{ 102,102,255 },
        Color{ 255,102,255 },
        Color{ 192,192,192 },
        Color{ 255,178,102 }
    };

    GameWindow(ScreenResolution = RES_1600_1024);
    ~GameWindow();

    GameWindow(GameWindow const&) = delete;
    void operator=(GameWindow const&) = delete;

    void CreateGeneralButtons();
    void CreateDistrictButtons();
    void CreateUnitButtons();
	void CreateRessourcesTextures();

public:
    static GameWindow& GetInstance()
    {

		static GameWindow m_instance{ };
        return m_instance;
    }

    void ShowWindow();
    SDL_Renderer* GetRenderer();
    void Close();

    bool IsClickInMap(const int& x, const int& y);
    bool IsClickInLeftMenu(const int& x, const int& y);

	void AddPopUpWindow(PopUpWindow * window);

	bool IsGameWindowInBackground();
};