#pragma once
#include "Unit.h"

class UnitSwordsmanII : public Unit<UnitSwordsmanII>
{
public:
    typedef Unit<UnitSwordsmanII> tBase;

    static int const ATTACK_DAMAGE = 75;
    static int const HEALTH = 125;
    static int const MOVE_RANGE = 1;
    static int const UNIT_TYPE = 6;
    static const char* UNIT_NAME;

public:
    UnitSwordsmanII(int owner);
    ~UnitSwordsmanII();
    virtual UnitBase* Clone();
    void LoadTexture();

    virtual bool CanUpgrade();
    virtual int GetMaxHealth();
    virtual const char* GetName();
    virtual int GetTypeAsInt();
    virtual void Heal(int health);

    virtual AttackNotification Attack(UnitBase* target);
    virtual AttackNotification Attack(DistrictBase* target);

    static UnitSwordsmanII* Deserialize(boost::property_tree::ptree node);
};

