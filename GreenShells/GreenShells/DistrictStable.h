#pragma once
#include "District.h"

class DistrictStable : public District<DistrictStable>
{
public:
    typedef District<DistrictStable> tBase;
    static const int DISTRICT_TYPE = 5;

    static const int ATTACK_DAMAGE = 75;
    static const int HEALTH = 300;

    static const int FOOD_COST = 200;
    static const int FOOD_BONUS = 0;
    static const int SCIENCE_BONUS = 0;
    static const int WEAPON_BONUS = 100;
    static int const VIEW_RANGE = 4;
    static const char* NAME;

public:
    DistrictStable(int owner);
    ~DistrictStable();
    virtual std::shared_ptr<DistrictBase> Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();

    static std::shared_ptr<DistrictStable> Deserialize(boost::property_tree::ptree node);
};



