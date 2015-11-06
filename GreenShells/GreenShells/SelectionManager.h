#pragma once
#include <vector>
#include "TileBase.h"
class Position;
class UnitBase;
class DistrictBase;
class Map;
enum ButtonState;

class SelectionManager
{
    enum SelectionManagerState
    {
        m_idle,
        m_createDistrict,
        m_unitMoving,
        m_unitAttacking
    };

    UnitBase* m_unitEmpty;
    DistrictBase* m_districtEmpty;

    SelectionManagerState m_state;

    //UnitBase * m_selectedUnit;
    //DistrictBase * m_selectedDistrict;
	Position m_selectedPosition;

    int m_districtTypeToConstruct;
    int m_unitTypeToCreate;
    
    SelectionManager(SelectionManager const&) = delete;
    void operator=(SelectionManager const&) = delete;
    std::vector<Position> m_actionPossibleTiles;
    SelectionManager();
    ~SelectionManager();

    void Idle(Position pos);
    void Attack(Position pos);
    void CreateDistrict(Position pos);
    void CreateUnit(Position pos);
    void Move(Position pos);

    void EndAction();

public:

    static SelectionManager& GetInstance()
    {
        static SelectionManager m_instance;
        return m_instance;
    }

    UnitBase* GetSelectedUnit();
    DistrictBase* GetSelectedDistrict();
    std::vector<Position> GetOverlayTiles();

	void ChangeButtonState();

    void Cancel();

    void HandleSelection(Position pos);

    void CreateDistrictPressed(int districtType);
    void CreateUnitPressed(int unitType);

    void UnitAttackPressed();
    void UnitMovePressed();

    bool IsAnUnitSelected();
    bool IsADistrictSelected();

    void UnitSell();
};
