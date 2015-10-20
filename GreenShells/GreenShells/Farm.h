#pragma once
#include "District.h"

class Farm : public District<Farm>
{
public:
	typedef District<Farm> tBase;
	static const int DISTRICT_TYPE = 1;

	static const int HEALTH = 75;

public:
	Farm(int owner);
	~Farm();

    void LoadTexture();
	virtual void Repair(int repairValue);

	virtual int GetTypeAsInt();

	static Farm* Deserialize(boost::property_tree::ptree node);
};