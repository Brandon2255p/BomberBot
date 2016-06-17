#include "Block.h"


cBlock::cBlock(const Json::Value &Entity, const Json::Value &Bomb, const Json::Value &PowerUp, const Json::Value &Exploding, const Json::Value &Location):
m_Entity(Entity),
m_Bomb(Bomb),
m_PowerUp(PowerUp),
m_Exploding(Exploding),
m_Location(Location)
{


	if (Entity.compare(Json::Value::nullRef))
	{
		if (Entity["$type"].asString() == "Domain.Entities.IndestructibleWallEntity, Domain")
			m_bIndestructibleWall = true;
		else if (Entity["$type"].asString() == ("Domain.Entities.DestructibleWallEntity, Domain"))
			m_bDestructableWall = true;
		else if (Entity["$type"].asString() == ("Domain.Entities.PlayerEntity, Domain"))
			m_bPlayer = true;
	}
	if (Bomb.isNull())
	{
		m_bBomb = false;
	}
	else m_bBomb = true;
	if (PowerUp.isNull())
	{
		m_bPowerUp = false;
	}
	else m_bPowerUp = true;

}


cBlock::~cBlock()
{
}

std::string cBlock::ToString()
{
	if (m_bDestructableWall)
		return "ITS A DESTRUCTABLE WALL! " + m_Entity["$type"].asString() + "\tX:" + std::to_string(m_Location.GetX()) + "\tY:" + std::to_string(m_Location.GetY());
	if (m_bIndestructibleWall)
		return "ITS AN INDESTRUCTABLE WALL! " + m_Entity["$type"].asString() + "\tX:" + std::to_string(m_Location.GetX()) + "\tY:" + std::to_string(m_Location.GetY());
	if (m_bPlayer)
		return "ITS A PLAYER! " + m_Entity["$type"].asString() + "\tX:" + std::to_string(m_Location.GetX()) + "\tY:" + std::to_string(m_Location.GetY());
	if (m_bPowerUp)
		return "ITS A POWERUP! " + m_PowerUp["$type"].asString() + "\tX:" + std::to_string(m_Location.GetX()) + "\tY:" + std::to_string(m_Location.GetY());
	if (m_bBomb)
		return "ITS A BOMB! " + m_Entity.asString() + "\tBomb:" + m_Bomb["Owner"]["Name"].asString() + "\tX:" + std::to_string(m_Location.GetX()) + "\tY:" + std::to_string(m_Location.GetY());
	return "ITS A NOTHING! " + m_Entity.asString() + "\tBomb:" + m_Bomb.asString() + "\tPowerUp:" + m_PowerUp.asString() + "\tExploding:" + m_Exploding.asString() + "\tX:" + std::to_string(m_Location.GetX()) + "\tY:" + std::to_string(m_Location.GetY());
}

bool cBlock::GetIsPowerUp()
{
	return m_bPowerUp;
}

bool cBlock::GetIsBomb()
{
	return m_bBomb;
}

cLocation cBlock::GetLocation()
{
	return m_Location;
}
