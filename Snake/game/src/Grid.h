#pragma once
#include "raylib.h"
//#include "main.cpp"

enum Direction {
	Left,
	Right,
	Up,
	Down
};

enum TileType {
	Empty,
	Snake,
	Wall,
	Food
};

////Grid settings
#define X_SIZE 22
#define Y_SIZE 22
#define Y_GRID_OFFSET 50 //Y Offset of the grid (to avoid drawing on the top of the top screen menu)

int GetCellSize();
int GetScale();
void SetScale(float value);

void SetGridTile(int x, int y, TileType value);
TileType GetGridTile(int x, int y);
void LoadGridTextures();
Vector2 GetPlayerPosition();
void SetPlayerPosition(Vector2 value);
void SetDirection(Direction value);
void SetLastDirection(Direction value);
Direction GetLastDirection();
Direction GetDirection();
Texture2D* GetGndTilesTextures(int id);
Texture2D* GetWallTilesTextures(int id);

Texture2D* GetSnakeBodyTex();
void DrawGrid();
void PlaceFood();
Vector2 GetNextPositionBlock(Direction dir);