#pragma once
#include <vector>
#include "Ptree_ForwardDeclaration.h"
#include "MapFilter.h"
#include "UtilitySkillTree.h"
#include "ArmySkillTree.h"
#include "EmpireSkillTree.h"

class Player
{
protected:
    std::string m_playerName;
    int m_playerID;
    bool m_isReadyForNewTurn;

    bool m_isAlive;
    bool m_isDisconnected;

    unsigned int m_cityCenterCount;
    unsigned int m_unitCount;

    unsigned int m_food;
    unsigned int m_science;
    unsigned int m_weapon;

    double m_foodMultiplier;
    double m_scienceMultiplier;
    double m_weaponMultiplier;

    UtilitySkillTree m_utilitySkillTree;
    ArmySkillTree m_armySkillTree;
    EmpireSkillTree m_empireSkillTree;

public:
    Player();
    ~Player();

    virtual Player* Clone() = 0;
    virtual void SetPlayerName(std::string name) = 0;
    std::string GetPlayerName();

    virtual void SetPlayerID(int ID) = 0;
    int GetPlayerID();

    virtual void NotifyNewTurn() = 0;

    virtual void SetPlayerReadyForNextTurn(bool isReady = true) = 0;
    bool IsPlayerReadyForNextTurn();

    virtual void SetIsAlive(bool value) = 0;
    bool IsAlive();
    int GetFood();
    int GetScience();
    int GetWeapon();

    virtual void AddFood(unsigned int qty) = 0;
    virtual void AddScience(unsigned int qty) = 0;
    virtual void AddWeapon(unsigned int qty) = 0;

    virtual bool ConsumeFood(unsigned int qty) = 0;
    virtual bool ConsumeScience(unsigned int qty) = 0;
    virtual bool ConsumeWeapon(unsigned int qty) = 0;

    virtual void AddFoodMultiplier(double multiplier) = 0;
    virtual void AddScienceMultiplier(double multiplier) = 0;
    virtual void AddWeaponMultiplier(double multiplier) = 0;

    // TODO : When gameplay will be more canon, see if the multiplier can go under 1.0 (Ennemy affecting my ratio)
    virtual void RemoveFoodMultiplier(double multiplier) = 0;
    virtual void RemoveScienceMultiplier(double multiplier) = 0;
    virtual void RemoveWeaponMultiplier(double multiplier) = 0;

    virtual void AddCityCenter() = 0;
    virtual void RemoveCityCenter() = 0;

    virtual void SetIsDisconnected(bool value = true) = 0;
    bool IsDisconnected();

	MapFilter GetMoveRestriction();

    virtual boost::property_tree::ptree Serialize();
};
