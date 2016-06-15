#include "Map.h"

#include <iostream>

cMapState::cMapState()
{
}


cMapState::~cMapState()
{
}


void cMapState::ClosestPowerUp(int X, int Y)
{
	if (X * Y > m_vMap.size())
		std::cerr << "ClosestPowerUp::Coord out of range X:" << X << " Y:" << Y << std::endl;
	else
	{

	}