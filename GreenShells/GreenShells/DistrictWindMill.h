#pragma once
#include "District.h"

class DistrictWindMill : public District<DistrictWindMill>
{
public:
    typedef District<DistrictWindMill> tBase;
    static const int DISTRICT_TYPE = 3;

    static const int ATTACK_DAMAGE = 0;
    static const int HEALTH = 350;

    static const int FOOD_COST = 400;
    static const int FOOD_BONUS = 175;
    static const int SCIENCE_BONUS = 0;
    static const int WEAPON_BONUS = 0;
    static int const VIEW_RANGE = 5;
    static const char* NAME;

public:
    DistrictWindMill(int owner);
    ~DistrictWindMill();
    virtual std::shared_ptr<DistrictBase> Clone();
    void LoadTexture();
    virtual void Repair(int repairValue);
    virtual bool CanUpgrade();

    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual void Upgrade(Map* map);

    static std::shared_ptr<DistrictWindMill> Deserialize(boost::property_tree::ptree node);
};

