#include "PlayerState.h"
#include <string>

PlayerState::PlayerState(const Json::Value &Name, const Json::Value &Key, const Json::Value &Points, const Json::Value &Killed, const Json::Value &BombBag, const Json::Value &BombRadius, const Json::Value &Location):
m_Name(Name),
m_Key(Key),
m_Points(Points),
m_Killed(Killed),
m_BombBag(BombBag),
m_BombRadius(BombRadius),
m_Location(Location)
{

}


PlayerState::~PlayerState()
{
}

std::string PlayerState::ToString()
{
	return m_Name.asString() + "\tKey:" + m_Key.asString() + "\tPoints:" + m_Points.asString() + "\tKilled:" + m_Killed.asString() + "\tBombBag:" + m_BombBag.asString() + "\tBombRad:" + m_BombRadius.asString() + "\tX:" + std::to_string(m_Location.GetX()) + "\tY:" + std::to_string(m_Location.GetY());
}

cLocation PlayerState::GetDistanceToPowerUp()
{

}

cLocation PlayerState::GetLocation()
{
	return m_Location;
}
