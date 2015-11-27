#include "UnitSwordsmanI.h"
#include <iostream>
#include "GameSession.h"
#include "ServerSession.h"
#include "Player.h"
#include "Map.h"
#include "UnitSwordsmanII.h"

const char* UnitSwordsmanI::UNIT_NAME = "Swordsman MK1";

UnitSwordsmanI::UnitSwordsmanI(int owner)
    : Unit<UnitSwordsmanI>(owner, HEALTH, ACTION_POINTS, MELEE_ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

UnitSwordsmanI::~UnitSwordsmanI()
{
}

std::shared_ptr<UnitBase> UnitSwordsmanI::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitSwordsmanI{ *this } };
}

void UnitSwordsmanI::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Units\\64x64\\sword.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitSwordsmanI::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    return player->GetArmySkillTree().SwordT2 && player->HasRessourcesForUnit(GetUnitTier());
}

int UnitSwordsmanI::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitSwordsmanI::GetName()
{
    return UNIT_NAME;
}

int UnitSwordsmanI::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitSwordsmanI::GetViewRange()
{
    return VIEW_RANGE;
}

int UnitSwordsmanI::GetUnitTier()
{
    return UNIT_TIER;
}

void UnitSwordsmanI::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitSwordsmanI::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

void UnitSwordsmanI::Upgrade(Map* map)
{
    map->GetTile(GetPosition())->SetUnit(std::shared_ptr<UnitBase>{new UnitSwordsmanII(GetOwnerID())});
}


// NEED TO PUT THIS IN EVERY MELEE UNIT, SO THEY CAN REECEIVE DAMAGE WHEN ATTACKING
AttackNotification UnitSwordsmanI::Attack(std::shared_ptr<UnitBase> target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

AttackNotification UnitSwordsmanI::Attack(std::shared_ptr<DistrictBase> target)
{
    UseActionPoints(ACTION_POINTS);
    AttackNotification targetNotification = UnitBase::Attack(target);
    AttackNotification attackerNotification = ReceiveDamage(targetNotification.RiposteDamage);

    targetNotification.AttackerIsDead = attackerNotification.TargetIsDead;
    targetNotification.CanMove = true;

    return targetNotification;
}

std::shared_ptr<UnitSwordsmanI> UnitSwordsmanI::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitSwordsmanI> swordsman = std::shared_ptr<UnitSwordsmanI>{ new UnitSwordsmanI(node.get<int>("<xmlattr>.O")) };
    swordsman->m_health = node.get<int>("<xmlattr>.H");
    swordsman->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return swordsman;
}