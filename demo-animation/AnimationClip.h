#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

enum class LoopTypes
{
	Single,
	Loop,
};

struct AnimationFrame
{
	//string textureId;
	Texture* texture;
	IntRect coord;
	Vector2f origin;

	AnimationFrame(Texture* t, const IntRect& c, const Vector2f& o)
		:texture(t), coord(c), origin(o)
	{
	}
};

struct AnimationClip
{
	string id;
	LoopTypes loopType;
	int fps;
	vector<AnimationFrame> frames;
};

