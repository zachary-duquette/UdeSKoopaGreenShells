#pragma once
#include "Texture.h"

enum ButtonState
{
    Unpressed,
    Pressed,
    Disabled
};

class Button
{
protected:
	// Not static (no curiously recurring template pattern like tile) 
	// because we do not need since only one button of each will exist;
	Texture m_textTexture;

    ButtonState m_buttonState;

    static const int VERTICAL_OFFSET = 38;
    static const int HORIZONTAL_OFFSET = 25;
    static const int BUTTON_HEIGHT = 50;
    static const int BUTTON_WIDTH = 90;

private:

    Texture m_unpressedButton;
    Texture m_pressedButton;
    const Color DISABLED_BUTTON_COLOR{ 192,192,192 };

	int m_topLimit;
	int m_botLimit;
	int m_rightLimit;
	int m_lefLimit;

    void LoadButtonTextures(SDL_Renderer* rend);
	virtual void LoadTextTexture(SDL_Renderer* rend) = 0;
public:
	Button(int sectionOffset, int columnIndex, int rowIndex, ButtonState state);
	~Button();

	bool IsInside(int xPos, int yPos);
    bool IsUnpressed();

	virtual void DoAction() = 0;
    void SetButtonState(ButtonState state);

	int GetTopY();
	int GetLeftX();

	int GetWidth();
	int GetHeight();

	/*
	* Omitting rend, and it will be rendered for the main game window
	*/
	Texture* GetTextTexture(SDL_Renderer* rend = nullptr);
	/*
	* Omitting rend, and it will be rendered for the main game window
	*/
    Texture* GetButtonTexture(SDL_Renderer* rend = nullptr);
};

