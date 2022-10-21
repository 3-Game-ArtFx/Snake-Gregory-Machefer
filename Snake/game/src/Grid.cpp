#include "Grid.h"
#include <stdlib.h>

TileType mGrid[X_SIZE][Y_SIZE]{ Empty };
//Size in pixel
int mCellSize = 32;

float mScale = 1;

//Textures
Texture2D mSnakeBodyTex;
Texture2D mSnakeHeadTex;
Texture2D mFoodTex;
Texture2D mGndTilesTex[3];
Texture2D mWallTilesTex[8];

Vector2 mPlayerPos;
Direction mDirection = Right;
Direction mLastDir = mDirection;

Texture2D* GetGndTilesTextures(int id) {
	return &mGndTilesTex[id];
}

Texture2D* GetWallTilesTextures(int id) {
	return &mWallTilesTex[id];
}

Direction GetDirection()
{
	return mDirection;
}

Direction GetLastDirection() 
{
	return mLastDir;
}

void SetDirection(Direction value) 
{
	mDirection = value;
}

void SetLastDirection(Direction value) 
{
	mLastDir = value;
}

Texture2D* GetSnakeBodyTex() 
{
	return &mSnakeBodyTex;
}

void SetPlayerPosition(Vector2 value) 
{
	mPlayerPos = value;
}

Vector2 GetPlayerPosition() 
{
	return mPlayerPos;
}

void LoadGridTextures() 
{
	mSnakeBodyTex = LoadTexture("Default/snakebody.png");
	mSnakeHeadTex = LoadTexture("Default/snakehead.png");

	mFoodTex = LoadTexture("Default/tile_0054.png");

	mGndTilesTex[0] = LoadTexture("Default/tile_0296.png");
	mGndTilesTex[1] = LoadTexture("Default/tile_0291.png");
	mGndTilesTex[2] = LoadTexture("Default/tile_0216.png");

	mWallTilesTex[0] = LoadTexture("Default/tile_0195.png");
	mWallTilesTex[1] = LoadTexture("Default/tile_0196.png");
	mWallTilesTex[2] = LoadTexture("Default/tile_0197.png");
	mWallTilesTex[3] = LoadTexture("Default/tile_0215.png");
	mWallTilesTex[4] = LoadTexture("Default/tile_0217.png");
	mWallTilesTex[5] = LoadTexture("Default/tile_0235.png");
	mWallTilesTex[6] = LoadTexture("Default/tile_0236.png");
	mWallTilesTex[7] = LoadTexture("Default/tile_0237.png");
}

int GetScale()
{
	return mScale;
}

void SetScale(float value) {
	mScale = value;
}

int GetCellSize()
{
	return mCellSize;
}

void SetGridTile(int x, int y, TileType value) 
{
	mGrid[x][y] = value;
}

TileType GetGridTile(int x, int y)
{
	return mGrid[x][y];
}

/// <summary>
/// Place a food on the grid
/// </summary>
void PlaceFood()
{
	Vector2 pos;

	//Pick a random place for the food
	do
	{
		pos.x = 1 + (rand() % (X_SIZE - 1));
		pos.y = 1 + (rand() % (Y_SIZE - 1));
	} while (GetGridTile((int)pos.x, (int)pos.y) != Empty);

	//Place food
	SetGridTile((int)pos.x, (int)pos.y, Food);
}

/// <summary>
/// Get the next position of the player
/// </summary>
/// <param name="dir">Direction enum</param>
/// <returns>Next player position</returns>
Vector2 GetNextPositionBlock(Direction dir)
{
	int x = 0;
	int y = 0;
	switch (dir)
	{
	case Right:
		if (GetPlayerPosition().x < X_SIZE)
			x = 1;
		break;

	case Left:
		if (GetPlayerPosition().x > 0)
			x = -1;
		break;

	case Down:
		if (GetPlayerPosition().y < Y_SIZE)
			y = 1;
		break;

	case Up:
		if (GetPlayerPosition().y > 0)
			y = -1;
		break;
	}
	Vector2 pos{ GetPlayerPosition().x + x , GetPlayerPosition().y + y };
	return pos;
}

void DrawGrid() 
{
	for (int x = 0; x < X_SIZE; x++)
	{
		for (int y = 0; y < Y_SIZE; y++)
		{
			if (mGrid[x][y] == Food)
			{
				Vector2 vec{ x * mCellSize , y * mCellSize + Y_GRID_OFFSET };

				DrawTextureEx(mFoodTex, vec, 0, mScale, WHITE);
			}
			else if (mGrid[x][y] == Snake)
			{
				//------------------------------------------------------------------------------------------ SNAKE
				Vector2 vec{ x * mCellSize , y * mCellSize + Y_GRID_OFFSET };

				if (x == mPlayerPos.x && y == mPlayerPos.y)
				{
					int rot = 0;
					if (mLastDir == Right)
					{
						rot = 90;
						vec.x += 32;
					}
					else if (mLastDir == Left)
					{
						rot = 270;
						vec.y += 32;
					}
					else if (mLastDir == Down)
					{
						rot = 180;
						vec.x += 32;
						vec.y += 32;
					}

					DrawTextureEx(mSnakeHeadTex, vec, rot, mScale, WHITE);
				}
				else
				{
					DrawTextureEx(mSnakeBodyTex, vec, 0, mScale, WHITE);
				}
			}
		}
	}
}