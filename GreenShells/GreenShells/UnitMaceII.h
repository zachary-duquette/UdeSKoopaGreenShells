#pragma once
#include "Unit.h"

class UnitMaceII : public Unit<UnitMaceII>
{
public:
    typedef Unit<UnitMaceII> tBase;

    static int const ATTACK_DAMAGE = 75;
    static int const ATTACK_RANGE = 1;
    static int const HEALTH = 300;
    static int const ACTION_POINTS = 2;
    static int const UNIT_TYPE = 9;
    static int const UNIT_TIER = 4;
    static int const VIEW_RANGE = 3;
    static const char* UNIT_NAME;

    UnitMaceII(int owner);
    virtual ~UnitMaceII();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual int GetViewRange();
    virtual void Heal(int health);
    virtual void NotifyNewTurn(int turn);

    virtual AttackNotification Attack(UnitBase* target);
    virtual AttackNotification Attack(DistrictBase* target);

    static UnitMaceII* Deserialize(boost::property_tree::ptree node);
};
