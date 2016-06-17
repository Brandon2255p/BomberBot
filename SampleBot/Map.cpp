#include "Map.h"
#include <math.h>
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
				std::cout << "Distance to player is: X" << iter.GetLocation().GetDistTo(ToThisLocation).GetX() << " Y:" << iter.GetLocation().GetDistTo(ToThisLocation).GetY() << std::endl;
			}
		}
	}
}

void cMapState::ClosestBomb(cLocation &ToThisLocation)
{
	int distance = 800;
	cLocation ClosestBomb;
	if (ToThisLocation.GetX() * ToThisLocation.GetY() > m_vMap.size())
		std::cerr << "ClosestBomb::Coord out of range X:" << ToThisLocation.GetX() << " Y:" << ToThisLocation.GetY() << std::endl;
	else
	{
		std::cout << "Player is at X:" << ToThisLocation.GetX() << " Y:" << ToThisLocation.GetY() << std::endl;
		for (auto iter : m_vMap)
		{
			if (iter.GetIsBomb())
			{
				int BombDist = sqrt(iter.GetLocation().GetDistTo(ToThisLocation).GetX() * iter.GetLocation().GetDistTo(ToThisLocation).GetX() + iter.GetLocation().GetDistTo(ToThisLocation).GetY() * iter.GetLocation().GetDistTo(ToThisLocation).GetY());
				if (BombDist < distance)
				{
					distance = BombDist;
					ClosestBomb.m_LocationX = iter.GetLocation().GetDistTo(ToThisLocation).GetX();
					ClosestBomb.m_LocationY = iter.GetLocation().GetDistTo(ToThisLocation).GetY();
				}
				std::cout << "FoundBomb at  X:" << iter.GetLocation().GetX() << " Y:" << iter.GetLocation().GetY() << std::endl;
			}
		}
		std::cout << "Closest bomb to player is: X" << ClosestBomb.GetX() << " Y:" << ClosestBomb.GetY() << " with a distance of " << distance << std::endl;

	}
}
