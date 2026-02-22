#pragma once
#include <string>

enum class DynosaurType
{
	TYRANNOSAURUS, VELOCIRAPTOR, BRACHIOSAURUS, DIPLODOCUS
};

struct Dynosaur
{
private:
	DynosaurType type;
	std::string name;
	int health;
	int attackPower;
public: 
	DynosaurType GetType() const;
	std::string GetName() const;
	Dynosaur(DynosaurType _type, std::string _name, int _attackPower) :
		type(_type), name(_name), health(100), attackPower(_attackPower) {};
	Dynosaur() = default;
	int GetStrength() const;

};
