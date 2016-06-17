#pragma once
#include "json\json.h"
#include "Location.h"
class cBlock
{
public:
	cBlock(const Json::Value &Entity, const Json::Value &Bomb, const Json::Value &PowerUp, const Json::Value &Exploding, const Json::Value &Location);
	~cBlock();
	std::string ToString();
	bool GetIsPowerUp();
	cLocation GetLocation();
	bool GetIsBomb();

private:
	const Json::Value m_Entity;
	const Json::Value m_Bomb;
	const Json::Value m_PowerUp;
	const Json::Value m_Exploding;
	cLocation m_Location;

	bool m_bPowerUp;
	bool m_bBomb;
	bool m_bIndestructibleWall;
	bool m_bDestructableWall;
	bool m_bPlayer;
};

