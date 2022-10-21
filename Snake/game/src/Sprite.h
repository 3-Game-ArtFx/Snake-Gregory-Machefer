#pragma once

#include "raylib.h"

class Sprite
{
public:
	Sprite();
	Sprite(Texture *tex, Vector2 position, Color color, float scale);
	Vector2 mPos;
	Texture2D* mpTex;
	Color mcolor;
	float mScale = 1;
	void Draw();
};

