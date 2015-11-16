#include "TileGround.h"
#include <iostream>
#include <string>
#include "District.h"

#include "UnitSettler.h"

#include "UnitArcherI.h"
#include "UnitArcherII.h"
#include "UnitArcherIII.h"

#include "UnitSwordsmanI.h"
#include "UnitSwordsmanII.h"
#include "UnitSwordsmanIII.h"

#include "UnitAxemanI.h"
#include "UnitAxemanII.h"

#include "UnitMaceI.h"
#include "UnitMaceII.h"

#include "UnitCannon.h"
#include "UnitShield.h"

#include "MapFilter.h"

#include "DistrictCityCenter.h"
#include "DistrictFarm.h"

#include "GameSession.h"

#include <boost\property_tree\ptree.hpp>


void TileGround::LoadTexture()
{
    try
    {
        TileGround::tBase::m_Texture.LoadFromFile("..\\Sprite\\Terrain\\64x64\\Grass.bmp");
    }
    catch (std::exception e)
    {
        std::string msg{ e.what() };
        std::cout << msg << std::endl;
    }
}

TileGround::TileGround(Position position)
    :Tile(position)
{
}

TileGround::~TileGround()
{
}

TileBase* TileGround::Clone()
{
    auto tile = new TileGround{ *this };
    if (m_district)
    {
        tile->m_district = m_district->Clone();
    }
    if (m_unit)
    {
        tile->m_unit = m_unit->Clone();
    }
    return tile;
}

TileGround* TileGround::Deserialize(boost::property_tree::ptree tileNode, Position pos)
{
    TileGround* tile = new TileGround{ pos };
    tile->m_owner = tileNode.get<int>("<xmlattr>.O");
    tile->m_playerDiscovered = tileNode.get<int>("<xmlattr>.D");

    for each(auto child in tileNode)
    {
        if (child.first == "U")
        {
            switch (child.second.get<int>("<xmlattr>.T"))
            {
            case UnitSwordsmanI::UNIT_TYPE:
                tile->SetUnit(UnitSwordsmanI::Deserialize(child.second));
                break;
            case UnitSwordsmanII::UNIT_TYPE:
                tile->SetUnit(UnitSwordsmanII::Deserialize(child.second));
                break;
            case UnitSwordsmanIII::UNIT_TYPE:
                tile->SetUnit(UnitSwordsmanIII::Deserialize(child.second));
                break;
            case UnitArcherI::UNIT_TYPE:
                tile->SetUnit(UnitArcherI::Deserialize(child.second));
                break; 
            case UnitArcherII::UNIT_TYPE:
                tile->SetUnit(UnitArcherII::Deserialize(child.second));
                break;
            case UnitArcherIII::UNIT_TYPE:
                tile->SetUnit(UnitArcherIII::Deserialize(child.second));
                break;
            case UnitSettler::UNIT_TYPE:
                tile->SetUnit(UnitSettler::Deserialize(child.second));
                break;
            case UnitAxemanI::UNIT_TYPE:
                tile->SetUnit(UnitAxemanI::Deserialize(child.second));
                break;
            case UnitAxemanII::UNIT_TYPE:
                tile->SetUnit(UnitAxemanII::Deserialize(child.second));
                break;
            case UnitCannon::UNIT_TYPE:
                tile->SetUnit(UnitCannon::Deserialize(child.second));
                break;
            case UnitShield::UNIT_TYPE:
                tile->SetUnit(UnitShield::Deserialize(child.second));
                break;
            case UnitMaceI::UNIT_TYPE:
                tile->SetUnit(UnitMaceI::Deserialize(child.second));
                break;
            case UnitMaceII::UNIT_TYPE:
                tile->SetUnit(UnitMaceII::Deserialize(child.second));
                break;
            }
        }
        else if (child.first == "D")
        {
            switch (child.second.get<int>("<xmlattr>.T"))
            {
            case DistrictCityCenter::DISTRICT_TYPE:
                tile->SetDistrict(DistrictCityCenter::Deserialize(child.second));
                break;
            case DistrictFarm::DISTRICT_TYPE:
                tile->SetDistrict(DistrictFarm::Deserialize(child.second));
                break;
            }
        }
    }

    return tile;
}

bool TileGround::CanTraverse(MapFilter filter)
{
    bool result = (filter & ALLOW_GROUND) != 0;

    if ((filter & BLOCK_ENEMIES) != 0)
    {
        int currentPlayerID = GameSession::GetInstance().GetCurrentPlayerID();

        if (m_unit != nullptr)
        {
            result &= currentPlayerID == m_unit->GetOwnerID();
        }

        if (m_district != nullptr)
        {
            result &= currentPlayerID == m_district->GetOwnerID();
        }

    }
    return  result;
}

int TileGround::GetTypeAsInt()
{
    return TILE_TYPE;
}