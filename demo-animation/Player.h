#pragma once
#include "Animator.h"

class Player
{
protected:
	Sprite sprite;
	Animator animator;

public:
	void Init();

	void UpdateInput(Event ev);

	void Update(float dt);
	void Draw(RenderWindow& window);
};

