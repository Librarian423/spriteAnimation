#include "Player.h"
#include "ResourceMgr.h"
#include <iostream>

void Player::Init()
{
	sprite.setPosition(1280.f / 2, 720.f / 2 + 60.f);
	animator.SetTarget(&sprite);

	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("Idle"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("Move"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("Jump"));

	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("IdleLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("MoveLeft"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("JumpLeft"));

	{
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
	}

	SetState(States::Idle);
	/*{
		AnimationClip clip;
		clip.id = "Idle";
		clip.fps = 10;
		clip.loopType = LoopTypes::Loop;
		for ( int i = 0; i < 8; i++ )
		{
			clip.frames.push_back(AnimationFrame(texture, { 120 * i,0,120,120 }, origin));
		}
		animator.AddClip(clip);

	}
	{
		AnimationClip clip;
		clip.id = "Move";
		clip.fps = 10;
		clip.loopType = LoopTypes::Loop;
		for ( int i = 0; i < 8; i++ )
		{
			clip.frames.push_back(AnimationFrame(texture, { 120 * i,120,120,120 }, origin));
		}
		clip.frames.push_back(AnimationFrame(texture, { 0,240,120,120 }, origin));
		animator.AddClip(clip);

	}
	{
		AnimationClip clip;
		clip.id = "Jump";
		clip.fps = 10;
		clip.loopType = LoopTypes::Single;
		for ( int i = 0; i < 7; i++ )
		{
			clip.frames.push_back(AnimationFrame(texture, { 120 * i,360,120,120 }, origin));
		}
		animator.AddClip(clip);

	}*/
}

void Player::SetState(States newState)
{
	if ( currState == newState )
	{
		return;
	}

	currState = newState;
	
	switch ( currState )
	{
	case Player::States::Idle:
		animator.Play((lastDirection.x > 0.f) ? "Idle" : "IdleLeft");
		break;
	case Player::States::Move:
		animator.Play((direction.x > 0.f) ? "Move" : "MoveLeft");
		break;
	case Player::States::Jump:
		animator.Play((lastDirection.x > 0.f) ? "Jump" : "JumpLeft");
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
		case Keyboard::Key::Space:
			SetState(States::Jump);
			break;
		
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

	switch ( currState )
	{
	case Player::States::Idle:
		UpdateIdle(dt);
		break;
	case Player::States::Move:
		UpdateMove(dt);
		break;
	case Player::States::Jump:
		UpdateJump(dt);
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

void Player::OnCompleteJump()
{
	SetState(States::Idle);
}

void Player::UpdateIdle(float dt)
{
	
	if ( !EqualFloat(direction.x, 0.f) )
	{
		SetState(States::Move);
		return;
	}
	
}

void Player::UpdateMove(float dt)
{
	if ( EqualFloat(direction.x, 0.f) )
	{
		SetState(States::Idle);
		return;
	}
	if ( !EqualFloat(direction.x, lastDirection.x) )
	{
		animator.Play((direction.x > 0.f) ? "Move" : "MoveLeft");
	}
}

void Player::UpdateJump(float dt)
{
}

bool Player::EqualFloat(float a, float b)
{
	return fabs(a - b) < numeric_limits<float>::epsilon();
}
