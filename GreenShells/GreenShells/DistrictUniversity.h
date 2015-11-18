#pragma once
#include "District.h"

class DistrictUniversity : public District<DistrictUniversity>
{
public:
    typedef District<DistrictUniversity> tBase;
    static const int DISTRICT_TYPE = 137;

    static const int ATTACK_DAMAGE = 75;
    static const int HEALTH = 400;

    static const int FOOD_COST = 0;
    static const int FOOD_BONUS = 0;
    static const int SCIENCE_BONUS = 0;
    static const int WEAPON_BONUS = 0;
    static int const VIEW_RANGE = 5;
    static const char* NAME;

public:
    DistrictUniversity(int owner);
    ~DistrictUniversity();
    virtual DistrictBase* Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();

    static DistrictUniversity* Deserialize(boost::property_tree::ptree node);
};




