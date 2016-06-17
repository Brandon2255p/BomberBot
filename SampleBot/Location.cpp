#include "stdafx.h"
#include "Location.h"


cLocation::cLocation(const Json::Value &Location)
{
	m_LocationX = Location["X"].asInt();
	m_LocationY = Location["Y"].asInt();
}

cLocation::cLocation()
{
	m_LocationX = 0;
	m_LocationY = 0;
}

cLocation::~cLocation()
{
}

int cLocation::GetX()
{
	return m_LocationX;
}

int cLocation::GetY()
{
	return m_LocationY;
}

cLocation cLocation::GetDistTo(const cLocation& rhs)
{
	cLocation Distance;
	Distance.m_LocationX = m_LocationX - rhs.m_LocationX;
	Distance.m_LocationY = m_LocationY - rhs.m_LocationY;
	return Distance;
}
