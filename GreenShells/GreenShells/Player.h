#pragma once
#include <vector>
#include <boost/serialization/access.hpp>
#include "Ptree_ForwardDeclaration.h"


class Player
{
    std::string m_playerName;
    int m_playerID;
    bool m_isReadyForNewTurn;

    bool m_isAlive;
    
    unsigned int m_cityHallCount;
    unsigned int m_unitCount;

    unsigned int m_food;
    unsigned int m_science;
    unsigned int m_weapon;

    double m_foodMultiplier;
    double m_scienceMultiplier;
    double m_weaponMultiplier;

	//Serialize
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & m_playerName;
		ar & m_playerID;
		ar & m_isReadyForNewTurn;
		ar & m_isAlive;
		ar & m_cityHallCount;
		ar & m_unitCount;
		ar & m_food;
		ar & m_science;
		ar & m_weapon;
		ar & m_foodMultiplier;
		ar & m_scienceMultiplier;
		ar & m_weaponMultiplier;
	}
public:
    Player();
    ~Player();

    int GetPlayerID();

    void NotifyNewTurn();

    void SetPlayerReadyForNextTurn(bool isReady = true);
    bool IsPlayerReadyForNextTurn();

	void SetDead();
	bool IsAlive();
    int GetFood();
    int GetScience();
    int GetWeapon();

    void AddFood(unsigned int qty);
    void AddScience(unsigned int qty);
    void AddWeapon(unsigned int qty);

    bool ConsumeFood(unsigned int qty);
    bool ConsumeScience(unsigned int qty);
    bool ConsumeWeapon(unsigned int qty);

    void AddFoodMultiplier(double multiplier);
    void AddScienceMultiplier(double multiplier);
    void AddWeaponMultiplier(double multiplier);

    // TODO : When gameplay will be more canon, see if the multiplier can go under 1.0 (Ennemy affecting my ratio)
    void RemoveFoodMultiplier(double multiplier);
    void RemoveScienceMultiplier(double multiplier);
    void RemoveWeaponMultiplier(double multiplier);


    boost::property_tree::ptree Serialize();
    static Player Deserialize(boost::property_tree::ptree playerNode);

};

