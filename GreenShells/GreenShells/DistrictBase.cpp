#include "DistrictBase.h"
#include <iostream>

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