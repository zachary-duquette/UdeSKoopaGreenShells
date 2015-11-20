#pragma once
#include "Unit.h"

class UnitShield : public Unit<UnitShield>
{
public:
    typedef Unit<UnitShield> tBase;

    static int const ATTACK_DAMAGE = 50;
    static int const ATTACK_RANGE = 1;
    static int const HEALTH = 400;
    static int const ACTION_POINTS = 1;
    static int const UNIT_TYPE = 11;
    static int const UNIT_TIER = 3;
    static const char* UNIT_NAME;

    UnitShield(int owner);
    virtual ~UnitShield();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual void Heal(int health);
    virtual void NotifyNewTurn(int turn);

    virtual AttackNotification Attack(UnitBase* target);
    virtual AttackNotification Attack(DistrictBase* target);

    static UnitShield* Deserialize(boost::property_tree::ptree node);
};