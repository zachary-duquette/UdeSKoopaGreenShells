#include "UnitBase.h"
#include <iostream>
#include <algorithm>
#include "DistrictBase.h"



UnitBase::UnitBase(int owner, int health, int attackRange, int attackDamage)
	: m_ownerID(owner),
	m_attackRange(attackRange),
	m_attackDamage(attackDamage),
	m_foodCost(0),
	m_scienceCost(0),
	m_weaponCost(0),
	m_health(health)
{
}

UnitBase::~UnitBase()
{
}

int UnitBase::GetAttackDamage()
{
	return m_attackDamage;
}

int UnitBase::GetHealth()
{
	return m_health;
}

int UnitBase::GetOwnerID()
{
	return m_ownerID;
}

Position UnitBase::GetPosition()
{
	return m_position;
}

void UnitBase::SetPosition(Position pos)
{
	m_position = pos;
}

AttackNotification UnitBase::ReceiveDamage(int damage)
{
	m_health -= damage;

	if (m_health <= 0)
		std::cout << "An unit die : Player " << m_ownerID << std::endl;

	return AttackNotification{ m_attackDamage / 2, (m_health <= 0), false };
}

AttackNotification UnitBase::Attack(UnitBase * target)
{
	AttackNotification targetNotification = target->ReceiveDamage(GetAttackDamage());

	return targetNotification;
}

AttackNotification UnitBase::Attack(DistrictBase * target)
{
	AttackNotification targetNotification = target->ReceiveDamage(GetAttackDamage());

	return targetNotification;
}

void UnitBase::NotifyNewTurn()
{
}