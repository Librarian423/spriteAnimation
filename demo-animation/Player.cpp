#include "Player.h"
#include "ResourceMgr.h"

void Player::Init()
{
	sprite.setPosition(512.f / 2, 512.f / 2 + 60.f);
	animator.SetTarget(&sprite);

	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("Idle"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("Move"));
	animator.AddClip(*ResourceMgr::GetInstance()->GetAnimationClip("Jump"));

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

void Player::UpdateInput(Event ev)
{
	switch ( ev.type )
	{
	case Event::KeyPressed:
		switch ( ev.key.code )
		{
		case Keyboard::Key::Num1:
			animator.Play("Idle");
			break;
		case Keyboard::Key::Num2:
			animator.Play("Move");
			break;
		case Keyboard::Key::Num3:
			animator.Play("Jump");
			break;

		case Keyboard::Key::Num4:
			animator.PlayQueue("Idle");
			break;
		case Keyboard::Key::Num5:
			animator.PlayQueue("Move");
			break;
		case Keyboard::Key::Num6:
			animator.Play("Jump");
			animator.PlayQueue("Move");
			break;
		case Keyboard::Key::Num7:
			animator.SetSpeed(2.0);
			break;
		case Keyboard::Key::Num8:
			animator.SetSpeed(1.0);
			break;
		case Keyboard::Key::Num9:
			animator.Stop();
			break;
		default:
			break;
		}
		break;
	}
}

void Player::Update(float dt)
{
	animator.Update(dt);
}

void Player::Draw(RenderWindow& window)
{
	window.draw(sprite);
}
