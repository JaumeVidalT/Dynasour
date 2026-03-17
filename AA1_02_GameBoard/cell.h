#pragma once
#include "Vector2.h"


struct Cell
{
private:
	char type;
public:
	Cell(char _type): type(_type){};
	Cell() = default;
	char GetType()const;
	void SetType(char newType);
};
