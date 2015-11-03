#include "SelectionManager.h"

#include <iostream>

#include "MapRemote.h"
#include "Position.h"
#include "ServerSession.h"
#include "Tile.h"
#include "GameSession.h"
#include "ClickManager.h"

#include "UnitEmpty.h"

#include "DistrictEmpty.h"
#include "DistrictCityCenter.h"
#include "DistrictFarm.h"

#include "ButtonUnitAttack.h"
#include "ButtonUnitCancel.h"
#include "ButtonUnitHeal.h"
#include "ButtonUnitMove.h"
#include "ButtonUnitSell.h"
#include "ButtonUnitUpgrade.h"

#include "ButtonDistrictCancel.h"
#include "ButtonDistrictRepair.h"
#include "ButtonDistrictSell.h"
#include "ButtonDistrictUpgrade.h"

#include "ButtonConstructDistrict.h"
#include "ButtonDiplomacy.h"
#include "ButtonSpawnUnit.h"
#include "ButtonGeneralCancel.h"
#include "ButtonSkillTree.h"

SelectionManager::SelectionManager()
	:m_selectedDistrict(new DistrictEmpty(-1))
	, m_selectedUnit(new UnitEmpty(-1))
	, m_state(m_idle)
	, m_unitEmpty(new UnitEmpty(-1))
	, m_districtEmpty(new DistrictEmpty(-1))
    , m_actionPossibleTiles()
	, m_districtTypeToConstruct(-1)
	, m_unitTypeToCreate(-1)
{
}

SelectionManager::~SelectionManager()
{
}

UnitBase* SelectionManager::GetSelectedUnit()
{
    return m_selectedUnit;
}

DistrictBase* SelectionManager::GetSelectedDistrict()
{
    return m_selectedDistrict;
}

std::vector<Position> SelectionManager::GetOverlayTiles()
{
    return m_actionPossibleTiles;
}

void SelectionManager::Cancel()
{
	DeselectUnit();
	DeselectDistrict();
	m_state = m_idle;
	m_actionPossibleTiles.clear();
}

void SelectionManager::DeselectUnit(UnitBase* unit)
{
	// TODO: need to be called when Unit dies
	if (unit == m_selectedUnit || unit == nullptr)
	{
		m_selectedUnit = m_unitEmpty;
		m_state = m_idle;
	}
}

void SelectionManager::DeselectDistrict(DistrictBase* district)
{
	// TODO: need to be called when District is destroyed
	if (district == m_selectedDistrict || district == nullptr)
	{
		m_selectedDistrict = m_districtEmpty;
	}
}

void SelectionManager::SelectUnit(UnitBase * unitToSelect)
{
	m_selectedUnit = unitToSelect ? unitToSelect : m_unitEmpty;
	m_state = m_idle;
}

void SelectionManager::SelectDistrict(DistrictBase * districtToSelect)
{
	m_selectedDistrict = districtToSelect ? districtToSelect : m_districtEmpty;
	m_state = m_idle;
}

void SelectionManager::ChangeButtonState()
{
	std::vector<Button*> unitButtons = ClickManager::GetInstance().GetUnitButtons();
	for (auto btn : unitButtons)
	{
		if (m_selectedUnit->GetOwnerID() != GameSession::GetInstance().GetCurrentPlayerID() && m_selectedUnit->GetActionRemaining() > 0 )
		{
			if (dynamic_cast<ButtonUnitAttack*>(btn) != nullptr)
			{
				if (m_state == m_unitAttacking)
				{
					btn->SetButtonState(ButtonState::Pressed);
				}
				else 
				{
					btn->SetButtonState(ButtonState::Unpressed);
				}
			}if (dynamic_cast<ButtonUnitMove*>(btn) != nullptr)
			{
				if (m_state == m_unitMoving)
				{
					btn->SetButtonState(ButtonState::Pressed);
				}
				else 
				{
					btn->SetButtonState(ButtonState::Unpressed);
				}
			}
			else if (dynamic_cast<ButtonUnitCancel*>(btn) != nullptr)
			{
				if (m_state == m_unitAttacking || m_state == m_unitMoving)
				{
					btn->SetButtonState(ButtonState::Unpressed);
				}
				else
				{
					btn->SetButtonState(ButtonState::Disabled);
				}
			}
			else if (dynamic_cast<ButtonUnitHeal*>(btn) != nullptr)
			{
				if (m_selectedUnit->GetHealth() < 100) // TODO : get max health for unit
				{
					btn->SetButtonState(ButtonState::Unpressed);
				}
				else
				{
					btn->SetButtonState(ButtonState::Disabled);
				}
			}
			else if (dynamic_cast<ButtonUnitSell*>(btn) != nullptr)
			{
				btn->SetButtonState(ButtonState::Unpressed);
			}
			else if (dynamic_cast<ButtonUnitUpgrade*>(btn) != nullptr)
			{
				if (m_selectedUnit->CanUpgrade())
				{
					btn->SetButtonState(ButtonState::Unpressed);
				}
				else
				{
					btn->SetButtonState(ButtonState::Disabled);
				}
			}
		}
		else
		{
			btn->SetButtonState(ButtonState::Disabled);
		}
		
	}
	
	std::vector<Button*> districtButtons = ClickManager::GetInstance().GetDistrictButtons();
	for (auto btn : districtButtons)
	{
		if (m_selectedDistrict->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID() && m_selectedDistrict->GetActionRemaining() > 0)
		{
			if (dynamic_cast<ButtonDistrictRepair*>(btn) != nullptr)
			{
				if (m_selectedDistrict->GetHealth() < 200) // TODO : GetMaxHeatlh
				{
					btn->SetButtonState(ButtonState::Unpressed);
				}
				else
				{
					btn->SetButtonState(ButtonState::Disabled);
				}
			}
			else if (dynamic_cast<ButtonDistrictSell*>(btn) != nullptr)
			{
				btn->SetButtonState(ButtonState::Unpressed);
			}
			else if (dynamic_cast<ButtonDistrictUpgrade*>(btn) != nullptr)
			{
				if (m_selectedDistrict->CanUpgrade())
				{
					btn->SetButtonState(ButtonState::Unpressed);
				}
				else
				{
					btn->SetButtonState(ButtonState::Disabled);
				}
			}
			else if (dynamic_cast<ButtonDistrictCancel*>(btn) != nullptr)
			{
				btn->SetButtonState(ButtonState::Disabled);
			}
		}
		else
		{
			btn->SetButtonState(ButtonState::Disabled);
		}
	}

	std::vector<Button*> generalButtons = ClickManager::GetInstance().GetGeneralButtons();
	for (auto btn : generalButtons)
	{
		if (dynamic_cast<ButtonDiplomacy*>(btn) != nullptr)
		{
			btn->SetButtonState(ButtonState::Unpressed);
		}
		else if (dynamic_cast<ButtonSkillTree*>(btn) != nullptr)
		{
			btn->SetButtonState(ButtonState::Unpressed);
		}
		else if (dynamic_cast<ButtonConstructDistrict*>(btn) != nullptr)
		{
			if (dynamic_cast<DistrictCityCenter*>(m_selectedDistrict) != nullptr && m_selectedDistrict->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID())
			{
				btn->SetButtonState(ButtonState::Unpressed);
			}
			else
			{
				btn->SetButtonState(ButtonState::Disabled);
			}
		}
		else if (dynamic_cast<ButtonSpawnUnit*>(btn) != nullptr)
		{
			if (dynamic_cast<DistrictCityCenter*>(m_selectedDistrict) != nullptr && m_selectedDistrict->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID())
			{
				btn->SetButtonState(ButtonState::Unpressed);
			}
			else
			{
				btn->SetButtonState(ButtonState::Disabled);
			}
		}
		else if (dynamic_cast<ButtonGeneralCancel*>(btn) != nullptr)
		{
			if (m_state == m_createDistrict)
			{
				btn->SetButtonState(ButtonState::Unpressed);
			}
			else
			{
				btn->SetButtonState(ButtonState::Disabled);
			}
		}
	}
}

void SelectionManager::Idle(UnitBase* unit, DistrictBase* district)
{
	SelectUnit(unit);
	SelectDistrict(district);

	ChangeButtonState();
}

void SelectionManager::Attack(Map * map, Position pos)
{
	map->Attack(GameSession::GetInstance().GetCurrentPlayerID(), m_selectedUnit->GetPosition(), pos); 
	EndAction();
}

void SelectionManager::CreateDistrict(Map * map, Position pos)
{
	map->CreateDistrict(m_districtTypeToConstruct, pos, GameSession::GetInstance().GetCurrentPlayerID());
	EndAction();
}

void SelectionManager::CreateUnit(Map * map, Position pos)
{
	map->CreateUnit(m_unitTypeToCreate, pos, GameSession::GetInstance().GetCurrentPlayerID());
	EndAction();
}

void SelectionManager::Move(Map * map, Position pos)
{
	map->MoveUnit(GameSession::GetInstance().GetCurrentPlayerID(), m_selectedUnit->GetPosition(), pos);
	EndAction();
}

void SelectionManager::EndAction()
{
	DeselectUnit();
	DeselectDistrict();
	m_state = m_idle;
	m_actionPossibleTiles.clear();

	ChangeButtonState();
}

void SelectionManager::HandleSelection(Position pos)
{
	//TODO taskID 8.2 Processus de selection
	Map* map = GameSession::GetInstance().GetWorldState()->GetMap();
	TileBase* tile = map->GetTile(pos);


	UnitBase* unit = tile->GetUnit();
	DistrictBase* district = tile->GetDistrict();
    
	// If the tile selected is not in our range of action possible, we remove the selected actor and do like no action was waiting
	if (m_state != m_idle && std::find(m_actionPossibleTiles.begin(), m_actionPossibleTiles.end(), tile->GetPosition()) == m_actionPossibleTiles.end())
	{
		Cancel();
	}

	switch (m_state)
	{
	case m_idle:
		std::cout << "Selecting Unit and district at pos " << pos.Column << " " << pos.Row << std::endl;
		Idle(unit, district);
		break;
	case  m_createDistrict:
		std::cout << "Create a district" << std::endl;
		CreateDistrict(map, pos);
		break;
	case m_unitMoving:
		std::cout << "Moving Unit" << std::endl;
		Move(map, pos);
		break;
	case m_unitAttacking:
		std::cout << "Attacking Unit" << std::endl;
		Attack(map, pos);
		
		break;
	default:
		break;
	}
}

void SelectionManager::CreateDistrictPressed(int districtType)
{
	if (IsAnDistrictSelected())
	{
		std::cout << "Selection Manager create district State" << std::endl;

		m_state = m_createDistrict;
		m_districtTypeToConstruct = districtType;

		Map map = GameSession::GetInstance().GetWorldState()->GetMapCopy();
		std::vector<Position> allPositionNear = map.GetArea(m_selectedDistrict->GetPosition(), 3 /* TODO : Validate where the constant will be (MaxBorderRange) */);
		
		m_actionPossibleTiles.clear();
		for (Position pos : allPositionNear)
		{
			if (map.GetTile(pos)->GetPlayerOwnerId() == GameSession::GetInstance().GetCurrentPlayerID() && map.GetTile(pos)->GetDistrict() == nullptr)
			{
				m_actionPossibleTiles.push_back(pos);
			}
		}
	}
}

void SelectionManager::CreateUnitPressed(int unitType)
{
	if (IsAnDistrictSelected())
	{
		m_unitTypeToCreate = unitType;
		CreateUnit(GameSession::GetInstance().GetWorldState()->GetMap(), m_selectedDistrict->GetPosition());
	}
}

void SelectionManager::UnitAttackPressed()
{
	if (IsAnUnitSelected())
	{
		std::cout << "Selection Manager attack State" << std::endl;

		m_state = m_unitAttacking;

		Map map = GameSession::GetInstance().GetWorldState()->GetMapCopy();
		std::vector<Position> allPositionNear = map.GetArea(m_selectedUnit->GetPosition(), m_selectedUnit->GetAttackRange());

		m_actionPossibleTiles.clear();
		for (Position pos : allPositionNear)
		{
			if ((map.GetTile(pos)->GetDistrict() != nullptr && map.GetTile(pos)->GetDistrict()->GetOwnerID() != GameSession::GetInstance().GetCurrentPlayerID()) ||
				(map.GetTile(pos)->GetUnit() != nullptr && map.GetTile(pos)->GetUnit()->GetOwnerID() != GameSession::GetInstance().GetCurrentPlayerID()))
			{
				m_actionPossibleTiles.push_back(pos);
			}
		}

		ChangeButtonState();
	}
}

void SelectionManager::UnitMovePressed()
{
	if (IsAnUnitSelected())
	{
		std::cout << "Selection Manager Move State" << std::endl;

		m_state = m_unitMoving;

		Map map = GameSession::GetInstance().GetWorldState()->GetMapCopy();
		Position unitPosition = m_selectedUnit->GetPosition();
		std::vector<Position> allPositionNear = map.GetArea(unitPosition, m_selectedUnit->GetMoveRange());

		m_actionPossibleTiles.clear();
		for (Position pos : allPositionNear)
		{
			if (pos != unitPosition && // Position is not the same
				map.GetTile(pos)->GetUnit() == nullptr && // No unit on the tile already
				(map.GetTile(pos)->GetDistrict() == nullptr || // No district on the tile
					(map.GetTile(pos)->GetDistrict()->GetOwnerID() == GameSession::GetInstance().GetCurrentPlayerID()))) // If there is a district on the tile, is it our?
			{
				m_actionPossibleTiles.push_back(pos);
			}
		}

		ChangeButtonState();
	}
}

bool SelectionManager::IsAnUnitSelected()
{
	return dynamic_cast<UnitEmpty*>(m_selectedUnit) == nullptr;
}

bool SelectionManager::IsAnDistrictSelected()
{
	return dynamic_cast<DistrictEmpty*>(m_selectedDistrict) == nullptr;
}

void SelectionManager::UnitSell()
{
	// TODO: Sell Unit
}
