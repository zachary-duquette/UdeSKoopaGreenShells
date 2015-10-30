#include "DistrictBase.h"
#include <iostream>
#include <boost\property_tree\ptree.hpp>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif // _DEBUG

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

DistrictBase::DistrictBase(int owner, int health, int attackDamage)
	: m_ownerID(owner),
	m_health(health),
	m_attackDamage(attackDamage),
	m_foodCost(0),
	m_scienceCost(0),
	m_weaponCost(0),
	m_foodRatioBonus(0.0),
	m_scienceRatioBonus(0.0),
	m_weaponRatioBonus(0.0)
{
}

DistrictBase::~DistrictBase()
{
}

int DistrictBase::GetAttackDamage()
{
	return m_attackDamage;
}

int DistrictBase::GetHealth()
{
	return m_health;
}

int DistrictBase::GetOwnerID()
{
	return m_ownerID;
}

Position DistrictBase::GetPosition()
{
	return m_position;
}

void DistrictBase::SetPosition(Position pos)
{
	m_position = pos;
}

AttackNotification DistrictBase::ReceiveDamage(int damage)
{
	m_health -= damage;

	if (m_health <= 0)
		std::cout << "A district got destroy : Player " << m_ownerID << std::endl;

	return AttackNotification{ m_attackDamage / 2, (m_health <= 0), false };
}

void DistrictBase::NotifyNewTurn()
{
}

boost::property_tree::ptree DistrictBase::Serialize()
{
	boost::property_tree::ptree districtNode;
	districtNode.put("<xmlattr>.T", GetTypeAsInt());
	districtNode.put("<xmlattr>.O", m_ownerID);
	districtNode.put("<xmlattr>.H", m_health);

	return districtNode;
}
