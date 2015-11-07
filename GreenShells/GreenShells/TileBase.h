#pragma once
#include "Texture.h"
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"
#include "MapFilter.h"

class DistrictBase;
class UnitBase;

class TileBase
{
    bool m_OverlayVisible;
protected:
    DistrictBase* m_district;
    UnitBase* m_unit;
    int m_owner;
    Position m_position;

public:

    virtual Color GetMinimapColor() =0;
    TileBase(Position position = Position(-1, -1));
    virtual ~TileBase();
    virtual TileBase* Clone() = 0;
    bool GetOverlayVisible();
    void SetOverlayVisible(bool visible);
    virtual Position GetPosition();
    virtual Texture* GetTexture() = 0;
    virtual bool CanTraverse(MapFilter filter)=0;
    virtual int GetTypeAsInt() = 0;
    virtual TileBase* Deserialize(boost::property_tree::ptree tileNode, Position pos);
    virtual void NotifyNewTurn(int turn);
    virtual DistrictBase* GetDistrict();
    virtual void SetDistrict(DistrictBase* district);
    virtual UnitBase* GetUnit();
    virtual void SetUnit(UnitBase* unit);
    virtual int GetPlayerOwnerId();
    virtual void SetPlayerOwnerId(int id);

    bool IsFree();
    boost::property_tree::ptree Serialize();
};
