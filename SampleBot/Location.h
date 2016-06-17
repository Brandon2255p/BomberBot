#pragma once
#include "json\json.h"
class cLocation
{
public:
	cLocation(const Json::Value &Location);
	cLocation();
	~cLocation();
	cLocation GetDistTo(const cLocation& rhs);
	int GetX();
	int GetY();
	int m_LocationX;
	int m_LocationY;
};

