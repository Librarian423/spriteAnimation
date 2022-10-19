#include "Animator.h"

Animator::Animator()
	:target(nullptr), speed(1.f), isPlaying(false), currClip(nullptr), currFrame(0), totalFrame(0), frameDuration(0.f), accumTime(0.f)
{
}

Animator::~Animator()
{
}

void Animator::AddClip(const AnimationClip& newClip)
{
	if ( clips.find(newClip.id) != clips.end() )
	{
		//error message
		return;
	}
	clips[newClip.id] = newClip;
}

void Animator::SetTarget(Sprite* t)
{
	target = t;
}

void Animator::Update(float dt)
{
	if ( !isPlaying )
	{
		return;
	}
	accumTime += dt * speed;
	if ( accumTime < frameDuration )
	{
		return;
	}

	accumTime = 0.f;
	++currFrame;

	if ( currFrame == totalFrame )
	{
		if ( !queue.empty() )
		{
			AnimationClip* front = queue.front();
			queue.pop();
			Play(front->id, false);;
		}
		else
		{
			switch ( currClip->loopType )
			{
			case LoopTypes::Single:
				currFrame = totalFrame - 1;
				break;
			case LoopTypes::Loop:
				currFrame = 0;
				break;
			}
		}
	}

	SetFrame(currClip->frames[currFrame]);
}

int Animator::GetCurrentFrame() const
{
	return currFrame;
}

void Animator::SetFrame(const AnimationFrame& frame)
{
	target->setTexture(*frame.texture);
	target->setTextureRect(frame.coord);
	target->setOrigin(frame.origin);
}

void Animator::Play(string id, bool clearQueue)
{
	if ( clearQueue )
	{
		ClearPlayQueue();
	}
	isPlaying = true;
	currClip = &clips[id];
	currFrame = 0;
	accumTime = 0.f;
	totalFrame = currClip->frames.size();
	frameDuration = 1.f / currClip->fps;
	SetFrame(currClip->frames[0]);
}

void Animator::PlayQueue(string id)
{
	queue.push(&clips[id]);
}

void Animator::Stop()
{
	isPlaying = false;
}

bool Animator::IsPlaying() const
{
	return isPlaying;
}

void Animator::ClearPlayQueue()
{
	while ( !queue.empty() )
	{
		queue.pop();
	}
}

float Animator::GetSpeed() const
{
	return speed;
}

void Animator::SetSpeed(float s)
{
	speed = s;
}