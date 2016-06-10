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
}


cBlock::~cBlock()
{
}

std::string cBlock::ToString()
{
	return m_Entity.asString() + "\tBomb:" + m_Bomb.asString() + "\tPowerUp:" + m_PowerUp.asString() + "\tExploding:" + m_Exploding.asString() + "\tX:" + m_LocationX.asString() + "\tY:" + m_LocationY.asString();
}

