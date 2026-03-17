#pragma once
#include "Vector2.h"

enum class PlayerMovement
{
	UP, DOWN, LEFT, RIGHT
};

struct Player
{
private:
	int score;
	char name;
public:
	Vector2 position;

	Player(Vector2 _position): position(_position), score(0), name('J') {};
	void AddScore();
	void SetPosition(Vector2 newPos);
	char GetName()const { return name; }
};
