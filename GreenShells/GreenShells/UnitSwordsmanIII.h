#pragma once
#include "Unit.h"

class UnitSwordsmanIII : public Unit<UnitSwordsmanIII>
{
public:
    typedef Unit<UnitSwordsmanIII> tBase;

    static int const ATTACK_DAMAGE = 100;
    static int const HEALTH = 150;
    static int const MOVE_RANGE = 1;
    static int const UNIT_TYPE = 7;
    static const char* UNIT_NAME;

public:
    UnitSwordsmanIII(int owner);
    ~UnitSwordsmanIII();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual void Heal(int health);

    virtual AttackNotification Attack(UnitBase* target);
    virtual AttackNotification Attack(DistrictBase* target);

    static UnitSwordsmanIII* Deserialize(boost::property_tree::ptree node);
};