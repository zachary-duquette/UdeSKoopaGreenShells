#pragma once
#include "District.h"

class DistrictFortress : public District<DistrictFortress>
{
public:
    typedef District<DistrictFortress> tBase;
    static const int DISTRICT_TYPE = 15;

    static const int ATTACK_DAMAGE = 75;
    static const int HEALTH = 400;

    static const int FOOD_COST = 0;
    static const int FOOD_BONUS = 0;
    static const int SCIENCE_BONUS = 0;
    static const int WEAPON_BONUS = 0;

    static const char* NAME;

public:
    DistrictFortress(int owner);
    ~DistrictFortress();
    virtual DistrictBase* Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();

    static DistrictFortress* Deserialize(boost::property_tree::ptree node);
};



