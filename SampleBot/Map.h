#pragma once
#include "Block.h"
#include <vector>
class cMapState
{
public:
	cMapState();
	~cMapState();

	std::vector<cBlock> m_vMap;

	void ClosestPowerUp(int X, int Y);
};

