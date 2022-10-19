#include "Player.h"
#include "ResourceMgr.h"
#include "Utils.h"
#include <iostream>

void Player::Init()
{
	sprite.setPosition(1280.f / 2, 720.f / 2 + 60.f);
	animator.SetTarget(&sprite);

	//animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("Idle"));
	//animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("Move"));
	//animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("Jump"));

	//animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("IdleLeft"));
	//animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MoveLeft"));
	//animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("JumpLeft"));

	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("IdleLeftUp"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("IdleRightUp"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("IdleLeftDown"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("IdleRightDown"));

	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("RunUp"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("RunDown"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("RunTopLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("RunTopRight"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("RunSideLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("RunSideRight"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("RunBottomLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("RunBottomRight"));

	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("AttackUp"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("AttackDown"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("AttackTopLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("AttackTopRight"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("AttackSideLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("AttackSideRight"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("AttackBottomLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("AttackBottomRight"));

	/*{
		AnimationEvent ev;
		ev.clipId = "Jump";
		ev.frame = 6;
		ev.onEvent = bind(&Player::OnCompleteJump, this);
		animator.AddEvent(ev);
	}
	{
		AnimationEvent ev;
		ev.clipId = "JumpLeft";
		ev.frame = 6;
		ev.onEvent = bind(&Player::OnCompleteJump, this);
		animator.AddEvent(ev);
	}*/

	SetState(States::IdleUp);
}

void Player::SetState(States newState)
{
	if ( currState == newState )
	{
		return;
	}
	prevState = currState;
	currState = newState;
	
	switch ( currState )
	{
	/*case Player::States::Idle:
		animator.Play((lastDirection.x > 0.f) ? "Idle" : "IdleLeft");
		break;
	case Player::States::Move:
		animator.Play((direction.x > 0.f) ? "Move" : "MoveLeft");
		break;
	case Player::States::Jump:
		animator.Play((lastDirection.x > 0.f) ? "Jump" : "JumpLeft");
		break;*/
	case Player::States::IdleUp:
		animator.Play((lastDirection.x > 0.f) ? "IdleRightUp" : "IdleLeftUp");
		break;
	case Player::States::IdleDown:
		animator.Play((lastDirection.x > 0.f) ? "IdleRightDown" : "IdleLeftDown");
		break;
	case Player::States::Run:
		animator.Play((direction.y > 0.f) ? "RunUp" : "RunDown");
		break;
	case Player::States::RunSide:
		animator.Play((direction.x < 0.f) ? "RunSideLeft" : "RunSideRight");
		break;
	}
}

void Player::UpdateInput(Event ev)
{
	switch ( ev.type )
	{
	case Event::KeyPressed:
		switch ( ev.key.code )
		{
		/*case Keyboard::Key::Space:
			SetState(States::Jump);
			break;*/
		/*case Keyboard::Key::Up:
			SetState(States::RunUp);
			break;
		case Keyboard::Key::Down:
			SetState(States::RunDown);
			break;*/
		case Keyboard::Key::Num9:
			animator.Stop();
			break;
		}
		break;
	}
}

void Player::Update(float dt)
{
	direction.x = 0.f;
	direction.x += Keyboard::isKeyPressed(Keyboard::Right) ? 1 : 0;
	direction.x += Keyboard::isKeyPressed(Keyboard::Left) ? -1 : 0;

	direction.y = 0.f;
	direction.y += Keyboard::isKeyPressed(Keyboard::Up) ? 1 : 0;
	direction.y += Keyboard::isKeyPressed(Keyboard::Down) ? -1 : 0;

	switch ( currState )
	{
	case Player::States::IdleUp:
		UpdateIdleUp(dt);
		break;
	case Player::States::IdleDown:
		UpdateIdleDown(dt);
		break;
	case Player::States::Run:
		UpdateRun(dt);
		break;
	case Player::States::RunTop:
		UpdateRunTop(dt);
		break;
	case Player::States::RunSide:
		UpdateRunSide(dt);
		break;
	}

	animator.Update(dt);
	if ( !EqualFloat(direction.x, 0.f) )
	{
		lastDirection = direction;
	}
	
}

void Player::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

//void Player::OnCompleteJump()
//{
//	SetState(States::Idle);
//}
//
//void Player::UpdateIdle(float dt)
//{
//	if ( !EqualFloat(direction.x, 0.f) )
//	{
//		SetState(States::Move);
//		return;
//	}
//}
//
//void Player::UpdateMove(float dt)
//{
//	if ( EqualFloat(direction.x, 0.f) )
//	{
//		SetState(States::Idle);
//		return;
//	}
//	if ( !EqualFloat(direction.x, lastDirection.x) )
//	{
//		animator.Play((direction.x > 0.f) ? "Move" : "MoveLeft");
//	}
//}

//void Player::UpdateJump(float dt)
//{
//}

void Player::UpdateIdleUp(float dt)
{
	if ( !EqualFloat(direction.x, 0.f) )
	{
		SetState(States::RunSide);
		return;
	}
	if ( !EqualFloat(direction.y, 0.f) )
	{
		SetState(States::Run);
		return;
	}
}

void Player::UpdateIdleDown(float dt)
{
	
	if ( !EqualFloat(direction.x, 0.f) )
	{
		SetState(States::RunSide);
		return;
	}
	if ( !EqualFloat(direction.y, 0.f) )
	{
		SetState(States::Run);
		return;
	}
	
}

void Player::UpdateRun(float dt)
{
	if ( EqualFloat(direction.y, 0.f) )
	{
		SetState(prevState);
		return;
	}
	if ( EqualFloat(direction.y, lastDirection.y) )
	{
		animator.Play((direction.y > 0.f) ? "RunUp" : "RunDown");
	}
}


void Player::UpdateRunTop(float dt)
{

}

void Player::UpdateRunSide(float dt)
{
	if ( EqualFloat(direction.x, 0.f) )
	{
		SetState(prevState);
		return;
	}
	if ( !EqualFloat(direction.x, lastDirection.x) )
	{
		animator.Play((direction.x < 0.f) ? "RunSideLeft" : "RunSideRight");
	}
}

void Player::UpdateRunBottom(float dt)
{
}

bool Player::EqualFloat(float a, float b)
{
	return fabs(a - b) < numeric_limits<float>::epsilon();
}
