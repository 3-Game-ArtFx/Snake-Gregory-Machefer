#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(Texture* tex, Vector2 position, Color color, float scale)
{
	mpTex = tex;
	mPos = position;
	mcolor = color;
	mScale = scale;
}

void Sprite::Draw() {
	//DrawTextureEx(tex, pos, 0, scale, CLITERAL(Color) { 30, 30, 30, 255 });
	DrawTextureEx(*mpTex, mPos, 0, mScale, mcolor);
}