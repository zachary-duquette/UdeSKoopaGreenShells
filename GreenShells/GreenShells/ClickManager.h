#pragma once
#include <vector>
#include "Button.h"
class Position;

enum LeftMenuPart
{
	GeneralPart,
	UnitPart,
	Building
};

class ClickManager
{
	ClickManager(ClickManager const&) = delete;
	void operator=(ClickManager const&) = delete;

	ClickManager();
	~ClickManager();

	std::vector<Button*> m_unitButton;
	std::vector<Button*> m_buildingButton;

public:
	static ClickManager& GetInstance()
	{
		static ClickManager m_instance;
		return m_instance;
	}

	void AddButton(Button* button, LeftMenuPart part);
	const std::vector<Button*>& GetUnitButton();

	void ManageMapClick(const Position& position);
	void ManageLeftMenuClick(const int& x, const int& y);
	void ManageTopMenuClick(const int& x, const int& y);
};

