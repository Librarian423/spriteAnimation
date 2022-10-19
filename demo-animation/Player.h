#pragma once
#include "Animator.h"

class Player
{
public:
	enum class States
	{
		None = -1,
		IdleUp,
		IdleDown,
		Run,//Up Down
		RunTop,
		RunSide,
		RunBottom,
		Attack,//Up Down
		AttackTop,
		AttackSide,
		AttackBottom,
	};

protected:
	
	Sprite sprite;
	Animator animator;

	States currState;
	States prevState;

	float speed;
	Vector2f direction;
	Vector2f lastDirection;

public:
	Player()
		:currState(States::None), speed(200.f), direction(1.f, 0.f), lastDirection(1.f, 0.f)
	{
	}

	void Init();

	void SetState(States newState);

	void UpdateInput(Event ev);
	void Update(float dt);
	void Draw(RenderWindow& window);

	/*void OnCompleteJump();

	void UpdateIdle(float dt);
	void UpdateMove(float dt);
	void UpdateJump(float dt);*/
	void UpdateIdleUp(float dt);
	void UpdateIdleDown(float dt);

	void UpdateRun(float dt);
	void UpdateRunTop(float dt);
	void UpdateRunSide(float dt);
	void UpdateRunBottom(float dt);


	bool EqualFloat(float a, float b);
};

