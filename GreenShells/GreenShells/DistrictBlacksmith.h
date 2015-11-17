#pragma once
#include "District.h"

class DistrictBlacksmith : public District<DistrictBlacksmith>
{
public:
    typedef District<DistrictBlacksmith> tBase;
    static const int DISTRICT_TYPE = 4;

    static const int ATTACK_DAMAGE = 75;
    static const int HEALTH = 250;

    static const int FOOD_COST = 150;
    static const int FOOD_BONUS = 0;
    static const int SCIENCE_BONUS = 0;
    static const int WEAPON_BONUS = 75;

    static const char* NAME;

public:
    DistrictBlacksmith(int owner);
    ~DistrictBlacksmith();
    virtual DistrictBase* Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();

    static DistrictBlacksmith* Deserialize(boost::property_tree::ptree node);
};

