#pragma once
#include "Unit.h"

class UnitAxemanII : public Unit<UnitAxemanII>
{
public:
    typedef Unit<UnitAxemanII> tBase;

    static int const ATTACK_DAMAGE = 225;
    static int const ATTACK_RANGE = 1;
    static int const HEALTH = 200;
    static int const MOVE_RANGE = 3;
    static int const UNIT_TYPE = 7;
    static int const UNIT_TIER = 3;
    static int const VIEW_RANGE = 4;
    static const char* UNIT_NAME;

    UnitAxemanII(int owner);
    virtual ~UnitAxemanII();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual int GetUnitTier();
    virtual void Heal(int health);

    virtual AttackNotification Attack(UnitBase* target);
    virtual AttackNotification Attack(DistrictBase* target);

    static UnitAxemanII* Deserialize(boost::property_tree::ptree node);
};