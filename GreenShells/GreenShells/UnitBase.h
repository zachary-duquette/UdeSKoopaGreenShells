#pragma once

#include "AttackNotification.h"
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"

class DistrictBase;
class Texture;

class UnitBase
{
public:
    static const int MELEE_ATTACK_RANGE = 1;

protected:
    //Serialized
    int m_health;
    int m_ownerID;
    Position m_position;
    int m_actionPointsLeft;

    //Unit Stats
    int m_foodCost;
    int m_scienceCost;
    int m_weaponCost;
    int m_attackDamage;
    int m_attackRange;

public:
    UnitBase(int owner, int health, int moveRange, int attackRange, int attackDamage);
    virtual ~UnitBase();

    virtual UnitBase* Clone() = 0;

    void UseActionPoints(int points);
    int GetActionPointsRemaining();
    int GetAttackDamage();
    int GetAttackRange();
    int GetHealth();
    int GetOwnerID();

    virtual int GetMaxHealth() = 0;
    virtual const char* GetName() = 0;
    virtual int GetTypeAsInt() = 0;

    Position GetPosition();
    void SetPosition(Position pos);

    virtual bool CanUpgrade() = 0;
    virtual Texture* GetTexture() = 0;
    virtual void Heal(int health) = 0;

    virtual AttackNotification Attack(UnitBase* target);
    virtual AttackNotification Attack(DistrictBase* target);

    AttackNotification ReceiveDamage(int damage);

    virtual void NotifyNewTurn(int turn);

    boost::property_tree::ptree Serialize();
};