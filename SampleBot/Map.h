#pragma once
#include "Block.h"
#include <vector>
#include "Location.h"
class cMapState
{
public:
	cMapState();
	~cMapState();

	std::vector<cBlock> m_vMap;

	void ClosestPowerUp(cLocation &ToThisLocation);
	void ClosestBomb(cLocation &ToThisLocation);

};

