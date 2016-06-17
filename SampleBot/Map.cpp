#include "Map.h"

#include <iostream>

cMapState::cMapState()
{
}


cMapState::~cMapState()
{
}


void cMapState::ClosestPowerUp(cLocation &ToThisLocation)
{
	if (ToThisLocation.GetX() * ToThisLocation.GetY() > m_vMap.size())
		std::cerr << "ClosestPowerUp::Coord out of range X:" << ToThisLocation.GetX() << " Y:" << ToThisLocation.GetY() << std::endl;
	else
	{
		std::cout << "Player is at X:" << ToThisLocation.GetX() << " Y:" << ToThisLocation.GetY() << std::endl;
		for (auto iter : m_vMap)
		{
			if (iter.GetIsPowerUp())
			{
				std::cout << "Power up at  X:" << iter.GetLocation().GetX() << " Y:" << iter.GetLocation().GetY() << std::endl;
				std::cout << "Distance to player is: X" << iter.GetLocation().GetDistTo(ToThisLocation).GetX() << " Y:" << iter.GetLocation().GetDistTo(ToThisLocation).GetY();
			}
		}
	}
}

void cMapState::ClosestBomb(cLocation &ToThisLocation)
{
	if (ToThisLocation.GetX() * ToThisLocation.GetY() > m_vMap.size())
		std::cerr << "ClosestBomb::Coord out of range X:" << ToThisLocation.GetX() << " Y:" << ToThisLocation.GetY() << std::endl;
	else
	{
		std::cout << "Player is at X:" << ToThisLocation.GetX() << " Y:" << ToThisLocation.GetY() << std::endl;
		for (auto iter : m_vMap)
		{
			if (iter.GetIsPowerUp())
			{
				std::cout << "ClosestBomb at  X:" << iter.GetLocation().GetX() << " Y:" << iter.GetLocation().GetY() << std::endl;
				std::cout << "Distance to player is: X" << iter.GetLocation().GetDistTo(ToThisLocation).GetX() << " Y:" << iter.GetLocation().GetDistTo(ToThisLocation).GetY();
			}
		}
	}
}
