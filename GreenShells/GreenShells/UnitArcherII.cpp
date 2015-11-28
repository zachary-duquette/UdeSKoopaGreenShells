#include "UnitArcherII.h"
#include <algorithm>
#include <iostream>
#include "GameSession.h"
#include "ServerSession.h"
#include "Player.h"

const char* UnitArcherII::UNIT_NAME = "Archer MK2";

UnitArcherII::UnitArcherII(int owner, bool hasBonusActionPoint)
    : Unit<UnitArcherII>(owner, HEALTH, ACTION_POINTS, ATTACK_RANGE, ATTACK_DAMAGE, VIEW_RANGE)
{
    if (hasBonusActionPoint)
    {
        m_actionPointsLeft += 1;
    }
}

UnitArcherII::~UnitArcherII()
{
}

std::shared_ptr<UnitBase> UnitArcherII::Clone()
{
    return std::shared_ptr<UnitBase> { new UnitArcherII{ *this } };
}

void UnitArcherII::LoadTexture()
{
    try
    {
        m_unitTexture.LoadFromFile("..\\Sprite\\Units\\64x64\\bow2.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

bool UnitArcherII::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    return player->GetArmySkillTree().RangerT3;
}

int UnitArcherII::GetMaxHealth()
{
    return HEALTH;
}

const char * UnitArcherII::GetName()
{
    return UNIT_NAME;
}

int UnitArcherII::GetTypeAsInt()
{
    return UNIT_TYPE;
}

int UnitArcherII::GetViewRange()
{
    return VIEW_RANGE;
}

void UnitArcherII::Heal(int health)
{
    m_health = std::min(m_health + health, HEALTH);
}

void UnitArcherII::NotifyNewTurn(int turn)
{
    m_actionPointsLeft = ACTION_POINTS;
    auto player = ServerSession::GetInstance().GetWorldState()->GetPlayerCopy(m_ownerID);
    if (player->GetUtilitySkillTree().MovementUpgrade)
    {
        m_actionPointsLeft += 1;
    }
}

std::shared_ptr<UnitArcherII> UnitArcherII::Deserialize(boost::property_tree::ptree node)
{
    std::shared_ptr<UnitArcherII> archer = std::shared_ptr<UnitArcherII>{ new UnitArcherII(node.get<int>("<xmlattr>.O")) };
    archer->m_health = node.get<int>("<xmlattr>.H");
    archer->m_actionPointsLeft = node.get<int>("<xmlattr>.APL");

    return archer;
}