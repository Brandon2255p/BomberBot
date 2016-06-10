#pragma once

#include "json\json.h"
#include <string>
class PlayerState
{
public:
	PlayerState(const Json::Value &Name, const Json::Value &Key, const Json::Value &Points, const Json::Value &Killed, const Json::Value &BombBag, const Json::Value &BombRadius, const Json::Value &Location);
	~PlayerState();
	std::string ToString();
private:
	const Json::Value m_Name;
	const Json::Value m_Key;
	const Json::Value m_Points;
	const Json::Value m_Killed;
	const Json::Value m_BombBag;
	const Json::Value m_BombRadius;
	const Json::Value m_Location;
	Json::Value m_LocationX;
	Json::Value m_LocationY;
};

