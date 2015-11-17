#include "UnitShield.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "Player.h"

const char* UnitShield::UNIT_NAME = "Shield";

UnitShield::UnitShield(int owner)
    : Unit<UnitShield>(owner, HEALTH, MOVE_RANGE, ATTACK_RANGE, ATTACK_DAMAGE)
{
}

UnitShield::~UnitShield()
{
}

UnitBase* UnitShield::Clone()
{
    return new UnitShield{ *this };
}

void UnitShield::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\shield.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitShield::CanUpgrade()
{
    return false;
}

int UnitShield::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitShield::GetName()
{
    return UNIT_NAME;
}

int UnitShield::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitShield::GetUnitTier()
{
    return UNIT_TIER;
}

void UnitShield::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

UnitShield * UnitShield::Deserialize(boost::property_tree::ptree node)
{
    UnitShield* cannon = new UnitShield(node.get<int>("<xmlattr>.O"));
    cannon->m_health = node.get<int>("<xmlattr>.H");

    return cannon;
}

AttackNotification UnitShield::Attack(UnitBase * target)
{
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitShield::Attack(DistrictBase * target)
{
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}