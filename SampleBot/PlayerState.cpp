#include "PlayerState.h"


PlayerState::PlayerState(const Json::Value &Name, const Json::Value &Key, const Json::Value &Points, const Json::Value &Killed, const Json::Value &BombBag, const Json::Value &BombRadius, const Json::Value &Location):
m_Name(Name),
m_Key(Key),
m_Points(Points),
m_Killed(Killed),
m_BombBag(BombBag),
m_BombRadius(BombRadius),
m_Location(Location)
{
	m_LocationX = m_Location["X"];
	m_LocationY = m_Location["Y"];
}


PlayerState::~PlayerState()
{
}

std::string PlayerState::ToString()
{
	return m_Name.asString() + " Key:" + m_Key.asString() + " Points:" + m_Points.asString() + " Killed:" + m_Killed.asString() + " BombBag:" + m_BombBag.asString() + " BombRad:" + m_BombRadius.asString() + " X:" + m_LocationX.asString() + " Y:" + m_LocationY.asString();
}
