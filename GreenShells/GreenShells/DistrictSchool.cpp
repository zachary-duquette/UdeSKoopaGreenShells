#include "GameSession.h"
#include <iostream>
#include "DistrictSchool.h"
#include "Player.h"
#include "Map.h"
#include "DistrictUniversity.h"

const char* DistrictSchool::NAME = "School";

DistrictSchool::DistrictSchool(int owner)
    : District<DistrictSchool>(owner, HEALTH, ATTACK_DAMAGE, FOOD_COST, FOOD_BONUS, SCIENCE_BONUS, WEAPON_BONUS)
{
}

std::shared_ptr<DistrictBase> DistrictSchool::Clone()
{
    return std::shared_ptr<DistrictBase> { new DistrictSchool{ *this } };
}

void DistrictSchool::LoadTexture()
{
    try
    {
        m_Texture.LoadFromFile("..\\Sprite\\Districts\\64x64\\school.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

DistrictSchool::~DistrictSchool()
{
}

void DistrictSchool::Repair(int repairValue)
{
    m_health = std::min(m_health + repairValue, HEALTH);
}

bool DistrictSchool::CanUpgrade()
{
    auto player = GameSession::GetInstance().GetWorldState()->GetPlayerCopy(GameSession::GetInstance().GetCurrentPlayerID());
    return player->GetUtilitySkillTree().University && player->HasRessourcesForDistrict(DistrictUniversity::DISTRICT_TYPE);
}

int DistrictSchool::GetMaxHealth()
{
    return HEALTH;
}

const char * DistrictSchool::GetName()
{
    return NAME;
}

int DistrictSchool::GetTypeAsInt()
{
    return DISTRICT_TYPE;
}

int DistrictSchool::GetViewRange()
{
    return VIEW_RANGE;
}

void DistrictSchool::Upgrade(Map * map)
{
    map->GetTile(GetPosition())->SetDistrict(std::shared_ptr<DistrictBase>{new DistrictUniversity(GetOwnerID())});
}

std::shared_ptr<DistrictSchool> DistrictSchool::Deserialize(boost::property_tree::ptree node)
{
    auto district = std::shared_ptr<DistrictSchool>{ new DistrictSchool(node.get<int>("<xmlattr>.O")) };
    district->m_health = node.get<int>("<xmlattr>.H");

    return district;
}