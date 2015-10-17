#pragma once
#include "Position.h"
#include <boost\property_tree\ptree.hpp>
#include "Texture.h"
#include "TileBase.h"


template<class T>
class Tile : public TileBase
{
private:
	//Serialize
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<TileBase>(*this);
	}
public:
	static Texture m_Texture;
	void LoadTexture() {};
    virtual  boost::property_tree::ptree Serialize() = 0;

	Tile()
		: TileBase()
	{

	}

    Tile(Position position = Position(-1, -1))
        : TileBase(position)
    {
    }

    ~Tile()
    {
    }

    virtual Tile* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position( -1, 0 ))
    {
        return nullptr;
    }

    //Every method must be define in header file because of the static polymorphism
	Texture* GetTexture()
	{
		if (!m_Texture.IsLoaded())
		{
			static_cast<T*>(this)->LoadTexture();
		}
		return &m_Texture;
	}
};

