#pragma once
#include "District.h"

class DistrictFarm : public District<DistrictFarm>
{
public:
    typedef District<DistrictFarm> tBase;
    static const int DISTRICT_TYPE = 1;
    static const int FOOD_YIELD = 3;
    static const int WEAPON_YIELD = 0;
    static const int SCIENCE_YIELD = 0;
    static const int FOOD_COST = 0;

    static const int HEALTH = 75;
    static const char* NAME;
    static int const VIEW_RANGE = 3;

public:
    DistrictFarm(int owner);
    ~DistrictFarm();
    virtual DistrictBase* Clone();
    virtual void ChangeOwner(int newOwner);
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();

    static DistrictFarm* Deserialize(boost::property_tree::ptree node);
};