#pragma once
#include "UnitBase.h"
#include "Texture.h"
#include <iostream>
#include <boost\property_tree\ptree.hpp>

template<class T>
class Unit : public UnitBase
{
public:
    static Texture m_unitTexture;
    static Texture m_boatTexture;
    void LoadTexture() {};
    static bool m_forceLoading;
    virtual int GetTypeAsInt() = 0;

public:
    Unit(int ownerID, int health, int moveRange, int attackRange, int attackDamage, int viewRange)
        : UnitBase(ownerID, health, moveRange, attackRange, attackDamage, viewRange)
    {
    }

    ~Unit()
    {
    }

    virtual std::shared_ptr<UnitBase> Clone() = 0;

    virtual std::shared_ptr<Unit> Deserialize(boost::property_tree::ptree tileNode, Position pos = Position(-1, 0))
    {
        return nullptr;
    }

    //Every method must be define in header file because of the static polymorphism
    Texture* GetUnitTexture()
    {
        if (m_forceLoading)
        {
            m_forceLoading = false;
            static_cast<T*>(this)->LoadTexture();

            try
            {
                m_boatTexture.LoadFromFile("..\\Sprite\\Units\\64x64\\boat.bmp");
            }
            catch (std::exception e)
            {
                std::string msg{ e.what() };
                std::cout << msg << std::endl;
            }

        }
        else if (!m_unitTexture.IsLoaded())
        {
            static_cast<T*>(this)->LoadTexture();
            m_forceLoading = false;
        }

        return &m_unitTexture;
    }

    //Every method must be define in header file because of the static polymorphism
    Texture* GetBoatTexture()
    {
        if (m_forceLoading)
        {
            m_forceLoading = false;
            static_cast<T*>(this)->LoadTexture();

            try
            {
                m_boatTexture.LoadFromFile("..\\Sprite\\Units\\64x64\\boat.bmp");
            }
            catch (std::exception e)
            {
                std::string msg{ e.what() };
                std::cout << msg << std::endl;
            }

        }
        else if (!m_boatTexture.IsLoaded())
        {
            try
            {
                m_boatTexture.LoadFromFile("..\\Sprite\\Units\\64x64\\boat.bmp");
            }
            catch (std::exception e)
            {
                std::string msg{ e.what() };
                std::cout << msg << std::endl;
            }
        }
        return &m_boatTexture;
    }

    static void ForceReload()
    {
        m_forceLoading = true;
    }
};