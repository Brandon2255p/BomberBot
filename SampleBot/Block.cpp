#include "Block.h"


cBlock::cBlock(const Json::Value &Entity, const Json::Value &Bomb, const Json::Value &PowerUp, const Json::Value &Exploding, const Json::Value &Location):
m_Entity(Entity),
m_Bomb(Bomb),
m_PowerUp(PowerUp),
m_Exploding(Exploding),
m_Location(Location)
{
	m_LocationX = m_Location["X"];
	m_LocationY = m_Location["Y"];

	if (Entity.compare(Json::Value::nullRef))
	{
		if (Entity["$type"].asString() == "Domain.Entities.IndestructibleWallEntity, Domain")
			m_bIndestructibleWall = true;
		else if (Entity["$type"].asString() == ("Domain.Entities.DestructibleWallEntity, Domain"))
			m_bDestructableWall = true;
		else if (Entity["$type"].asString() == ("Domain.Entities.PlayerEntity, Domain"))
			m_bPlayer = true;
	}
	if (Bomb.compare(Json::Value::null))
	{
		m_bBomb = true;
	}
	if (PowerUp.compare(Json::Value::null))
	{
		m_bPowerUp = true;
	}

}


cBlock::~cBlock()
{
}

std::string cBlock::ToString()
{
	if (m_bDestructableWall)
		return "ITS A DESTRUCTABLE WALL! " + m_Entity["$type"].asString() + "\tX:" + m_LocationX.asString() + "\tY:" + m_LocationY.asString();
	if (m_bIndestructibleWall)
		return "ITS AN INDESTRUCTABLE WALL! " + m_Entity["$type"].asString() + "\tX:" + m_LocationX.asString() + "\tY:" + m_LocationY.asString();
	if (m_bPlayer)
		return "ITS A PLAYER! " + m_Entity["$type"].asString() + "\tX:" + m_LocationX.asString() + "\tY:" + m_LocationY.asString();
	if (m_bPowerUp)
		return "ITS A POWERUP! " + m_PowerUp["$type"].asString() + "\tX:" + m_LocationX.asString() + "\tY:" + m_LocationY.asString();
	if (m_bBomb)
		return "ITS A BOMB! " + m_Entity.asString() + "\tBomb:" + m_Bomb["Owner"]["Name"].asString() + "\tX:" + m_LocationX.asString() + "\tY:" + m_LocationY.asString();
	return "ITS A NOTHING! " + m_Entity.asString() + "\tBomb:" + m_Bomb.asString() + "\tPowerUp:" + m_PowerUp.asString() + "\tExploding:" + m_Exploding.asString() + "\tX:" + m_LocationX.asString() + "\tY:" + m_LocationY.asString();
}

