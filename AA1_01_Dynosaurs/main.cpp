#include <string>
#include <cmath>
#include "dynasour.h"
#include <iostream>

const int MAX_DYNOSAURS = 15;

std::string getDynasaurTypeToString(const Dynosaur dyn)
{
	return dyn.GetName();
}

bool compareDynosaurStrength(const Dynosaur& dyn1,const Dynosaur& dyn2)
{
	return dyn1.GetStrength() != dyn2.GetStrength();
}
Dynosaur createRandomDynosaur()
{
	int typeChoice = rand() % 4;
	DynosaurType type;
	std::string name;
	int attackPower;

	switch (typeChoice)
	{
	case 0:
		type = DynosaurType::TYRANNOSAURUS;
		name = "TYRANNOSAURUS";
		attackPower = 100;
		break;
	case 1:
		type = DynosaurType::VELOCIRAPTOR;
		name = "VELOCIRAPTOR";
		attackPower = 80;
		break;
	case 2:
		type = DynosaurType::BRACHIOSAURUS;
		name = "BRACHIOSAURUS";
		attackPower = 65;
		break;
	case 3:
		type = DynosaurType::DIPLODOCUS;
		name = "DIPLODOCUS";
		attackPower = 45;
		break;
	}
	Dynosaur dyn(type, name, attackPower);
	return dyn;
}

void main()
{
	srand(time(NULL));
	Dynosaur* jurassicPark= new Dynosaur[MAX_DYNOSAURS];
	for (int i = 0; i < MAX_DYNOSAURS; ++i)
	{
		if (i % 2 == 0)
		{
			jurassicPark[i] = createRandomDynosaur();
			if (i != 0)
			{
				if (!compareDynosaurStrength(jurassicPark[i], jurassicPark[i - 2]))
				{
					i--;
				}
			}
		}
	}
	for (int i = 0; i < MAX_DYNOSAURS; ++i)
	{
		if (jurassicPark[i].GetName() != "")
		{
			std::cout << jurassicPark[i].GetName()<< std::endl;
		}
		else
		{
			std::cout << "No hay Dinosaurio" << std::endl;
		}
		
	}
	delete[] jurassicPark;
}