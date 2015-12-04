#pragma once
#include "Map.h"

class MapLocal : public Map
{
public:
    MapLocal();
    ~MapLocal();
    Map* Clone();

    void DiscoverArea(Position pos, int range, int playerId);
    void RemoveFogOfWarForPlayer(int playerID);

    virtual bool MoveUnit(int ownerID, Position unitLocation, Position newLocation, int actionCost);
    virtual bool Attack(int ownerID, Position attackerPosition, Position targetPosition, int actionCost);
    virtual bool CreateUnit(int unitType, Position pos, int owner, bool upgrade);
    virtual bool CreateDistrict(int districtType, Position pos, int owner, bool upgrade);
    virtual bool SellDistrict(Position pos, int owner);
    virtual bool SellUnit(Position pos, int owner);
    virtual bool UpgradeUnit(Position pos, int owner);
    virtual bool UpgradeDistrict(Position pos, int owner);
    virtual bool HealUnit(Position pos, int owner);
    virtual bool RepairDistrict(Position pos, int owner);

    static MapLocal* Deserialize(boost::property_tree::ptree mapNode);
};