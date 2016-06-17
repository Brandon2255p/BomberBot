#pragma once

#include "json\json.h"
#include <string>
#include "Location.h"
class PlayerState
{
public:
	PlayerState(const Json::Value &Name, const Json::Value &Key, const Json::Value &Points, const Json::Value &Killed, const Json::Value &BombBag, const Json::Value &BombRadius, const Json::Value &Location);
	~PlayerState();
	std::string ToString();
	cLocation GetDistanceToPowerUp();
	cLocation GetLocation();
private:
	const Json::Value m_Name;
	const Json::Value m_Key;
	const Json::Value m_Points;
	const Json::Value m_Killed;
	const Json::Value m_BombBag;
	const Json::Value m_BombRadius;
	cLocation m_Location;
	cLocation m_DistToPowerUp;

};

