#pragma once
#include "json\json.h"
class cBlock
{
public:
	cBlock(const Json::Value &Entity, const Json::Value &Bomb, const Json::Value &PowerUp, const Json::Value &Exploding, const Json::Value &Location);
	~cBlock();
	std::string ToString();
private:
	const Json::Value m_Entity;
	const Json::Value m_Bomb;
	const Json::Value m_PowerUp;
	const Json::Value m_Exploding;
	const Json::Value m_Location;
	Json::Value m_LocationX;
	Json::Value m_LocationY;
};

