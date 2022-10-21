#include "raylib.h"
#include "Sprite.h"
#include "Grid.h"
#include "Menu.h"
#include <vector>
#include <string>
#include <iostream>

enum GameState {
	Win,
	Lose,
	Playing,
	Starting,
	StartMenu,
	Pause
};

////Game
GameState mState = StartMenu;

//Game settings
int mMoveSpeed = 8; //Lower is quicker

////Player
//Player movements

int mMoveTimer = 0;

//All player body blocs positions
std::vector<Vector2> mPlayerPosHistory;
std::vector<Sprite> mPropsSprites;


//Starting game timers
int mStartingTimer = 0;

//In game timer
int mSecondTimer = 0;

//Sounds
Sound mLoseSound;
Sound mEatSound;

/// <summary>
/// Remove the last player (snake) sprite block
/// </summary>
void RemoveLastPlayerBlock()
{
	Vector2 pos = mPlayerPosHistory[0];
	SetGridTile((int)pos.x, (int)pos.y, Empty);
	mPlayerPosHistory.erase(mPlayerPosHistory.begin());
}

/// <summary>
/// Load all game sounds
/// </summary>
void LoadSounds()
{
	mLoseSound = LoadSound("Audio/jingles_NES00.ogg");
	SetSoundVolume(mLoseSound, 0.1);
	mEatSound = LoadSound("Audio/jingles_NES01.ogg");
	SetSoundVolume(mEatSound, 0.05);
}


/// <summary>
/// Set grid walls (collisions and sprites)
/// </summary>
void SetWalls()
{
	//-------------- Reset grid
	for (int x = 0; x < X_SIZE; x++)
	{
		for (int y = 0; y < Y_SIZE; y++)
		{
			SetGridTile(x, y, Empty);
		}
	}

	//-------------- Set collision
	for (int i = 0; i < X_SIZE; i++)
	{
		//Top and bottom
		SetGridTile(i, 0, Wall);
		SetGridTile(i, Y_SIZE - 1, Wall);

		//Left and right
		SetGridTile(0, i, Wall);
		SetGridTile(X_SIZE - 1, i, Wall);
	}
	mPropsSprites.clear();

	//Create grid walls
	for (int i = 1; i < X_SIZE - 1; i++)
	{
		//-------------- Create sprites
		Vector2 pos;
		pos.x = i * 32;
		pos.y = Y_GRID_OFFSET;
		mPropsSprites.emplace_back(Sprite(GetWallTilesTextures(1), pos, WHITE, GetScale()));

		pos.x = i * 32;
		pos.y = Y_GRID_OFFSET + (Y_SIZE - 1) * GetCellSize();
		mPropsSprites.emplace_back(Sprite(GetWallTilesTextures(6), pos, WHITE, GetScale()));

		pos.x = 0;
		pos.y = Y_GRID_OFFSET + i * 32;
		mPropsSprites.emplace_back(Sprite(GetWallTilesTextures(3), pos, WHITE, GetScale()));

		pos.x = (X_SIZE - 1) * GetCellSize();
		pos.y = Y_GRID_OFFSET + i * 32;
		mPropsSprites.emplace_back(Sprite(GetWallTilesTextures(4), pos, WHITE, GetScale()));
	}

	//Map corners
	Vector2 pos;
	pos.x = (X_SIZE - 1) * GetCellSize();
	pos.y = Y_GRID_OFFSET;
	mPropsSprites.emplace_back(Sprite(GetWallTilesTextures(2), pos, WHITE, GetScale()));

	pos.x = 0;
	pos.y = Y_GRID_OFFSET;
	mPropsSprites.emplace_back(Sprite(GetWallTilesTextures(0), pos, WHITE, GetScale()));

	pos.x = 0;
	pos.y = Y_GRID_OFFSET + (Y_SIZE - 1) * GetCellSize();
	mPropsSprites.emplace_back(Sprite(GetWallTilesTextures(5), pos, WHITE, GetScale()));

	pos.x = (X_SIZE - 1) * GetCellSize();
	pos.y = Y_GRID_OFFSET + (Y_SIZE - 1) * GetCellSize();
	mPropsSprites.emplace_back(Sprite(GetWallTilesTextures(7), pos, WHITE, GetScale()));

	//Add propos
	int propsCount = 5 + rand() % 5;
	for (int i = 0; i < propsCount; i++)
	{
		Vector2 pos{ 32 + 32 * (rand() % 20) , 32 + Y_GRID_OFFSET + 32 * (rand() % 20) };
		Sprite sprite = Sprite(GetGndTilesTextures(rand() % 3), pos, CLITERAL(Color) { 30, 30, 30, 255 }, GetScale());
		mPropsSprites.emplace_back(sprite);
	}
}

/// <summary>
/// Set move speed with difficulty
/// </summary>
void SetMoveSpeed()
{
	switch (GetDifficulty())
	{
	case Easy:
		mMoveSpeed = 20;
		break;
	case Medium:
		mMoveSpeed = 14;
		break;
	case Hard:
		mMoveSpeed = 8;
		break;
	case Hardcore:
		mMoveSpeed = 5;
		break;
	case Impossible:
		mMoveSpeed = 3;
		break;
	}
}

/// <summary>
/// Init party
/// </summary>
void InitParty()
{
	//Reset timers
	SetStartingCounter(3);
	mStartingTimer = 0;
	mMoveTimer = 0;
	SetScore(0);
	SetSeconds(0);
	mSecondTimer = 0;
	SetDirection(Right);
	SetLastDirection(GetDirection());

	SetWalls();

	SetMoveSpeed();

	//Reset player position
	SetPlayerPosition(Vector2{ 10,10 });

	//Set player collision
	SetGridTile((int)GetPlayerPosition().x, (int)GetPlayerPosition().y, Snake);
	SetGridTile((int)GetPlayerPosition().x - 1, (int)GetPlayerPosition().y, Snake);
	SetGridTile((int)GetPlayerPosition().x - 2, (int)GetPlayerPosition().y, Snake);

	//Reset player position history
	mPlayerPosHistory.clear();

	Vector2 v1{ (int)GetPlayerPosition().x - 2 , (int)GetPlayerPosition().y };
	mPlayerPosHistory.emplace_back(v1);

	v1.x = (int)GetPlayerPosition().x - 1;
	v1.y = (int)GetPlayerPosition().y;
	mPlayerPosHistory.emplace_back(v1);

	v1.x = (int)GetPlayerPosition().x;
	v1.y = (int)GetPlayerPosition().y;
	mPlayerPosHistory.emplace_back(v1);

	PlaceFood();
}

/// <summary>
/// Draw all sprites
/// </summary>
void DrawSprites()
{
	for (int i = 0; i < mPropsSprites.size(); i++)
	{
		mPropsSprites[i].Draw();
	}
}


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
	srand(time(NULL));
	InitAudioDevice();      // Initialize audio device
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
	InitWindow(screenWidth, screenHeight, "Black'n White Snake");

	//Disable esc detection
	SetExitKey(0);

	LoadSounds();
	LoadGridTextures();

	//Set sprite scale (depending of the windows size to get a pixel perfect view)
	SetScale(screenWidth / X_SIZE / GetSnakeBodyTex()->height);

	InitParty();

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button
	{
		//Change snake direction (check the last direction to avoid reverse direction)
		if (IsKeyDown(KEY_RIGHT))
		{
			if (GetLastDirection() != Left)
				SetDirection(Right);
		}
		if (IsKeyDown(KEY_LEFT))
		{
			if (GetLastDirection() != Right)
				SetDirection(Left);
		}
		if (IsKeyDown(KEY_DOWN))
		{
			if (GetLastDirection() != Up)
				SetDirection(Down);
		}
		if (IsKeyDown(KEY_UP))
		{
			if (GetLastDirection() != Down)
				SetDirection(Up);
		}

		//------------------------------------------------------------------------------------------ Draw
		BeginDrawing();

		ClearBackground(BLACK);

		DrawSprites();
		DrawGrid();
		DrawTopMenu();

		//Starting counter
		if (mState == Starting)
		{
			mStartingTimer++;
			if (mStartingTimer == 60)
			{
				SetStartingCounter(GetStartingCounter() - 1);
				mStartingTimer = 0;
			}

			if (GetStartingCounter() == -1) //If the timer ends, start the party
			{
				mState = Playing;
			}
			else
			{
				DrawStartingMenu();
			}
		}
		else if (mState == Lose) //Draw and control the lose menu
		{
			if (IsKeyPressed(KEY_SPACE))
			{
				mState = StartMenu;
				InitParty();
			}
			DrawLoseMenu();
		}
		else if (mState == Playing) //Draw and control the playing 
		{
			//Increase game timer
			mSecondTimer++;
			if (mSecondTimer == 60)
			{
				mSecondTimer = 0;
				SetSeconds(GetSeconds() + 1);
			}

			//Increase move timer
			mMoveTimer++;
			if (mMoveTimer == mMoveSpeed)
			{
				mMoveTimer = 0;
				SetLastDirection(GetDirection());
				Vector2 newPos = GetNextPositionBlock(GetDirection());

				//If the next tile is empty or the tail of the snake
				if (GetGridTile((int)newPos.x, (int)newPos.y) == Empty || (mPlayerPosHistory[0].x == (int)newPos.x && mPlayerPosHistory[0].y == (int)newPos.y))
				{
					RemoveLastPlayerBlock();

					//Place new snake tile
					SetGridTile((int)newPos.x, (int)newPos.y, Snake);
					SetPlayerPosition(newPos);
					mPlayerPosHistory.emplace_back(newPos);
				}
				else if (GetGridTile((int)newPos.x, (int)newPos.y) == Food) //If the next tile is a food item
				{
					//Place new snake tile
					SetGridTile((int)newPos.x, (int)newPos.y, Snake);
					SetPlayerPosition(newPos);
					mPlayerPosHistory.emplace_back(newPos);

					PlaceFood();
					PlaySound(mEatSound);
					SetScore(GetScore() + 1);
				}
				else //If the snake hits a wall or itself
				{
					if (GetScore() > GetBestScore())
						SetBestScore(GetScore());

					PlaySound(mLoseSound);
					mState = Lose;
				}
			}
		}
		else if (mState == StartMenu) //Draw and control the start menu
		{
			DrawStartMenu();
			if (IsKeyPressed(KEY_RIGHT))
			{
				if ((int)GetDifficulty() < Impossible)
					SetDifficulty(GetDifficulty() + 1);
				else
					SetDifficulty(0);
			}
			if (IsKeyPressed(KEY_LEFT))
			{
				if ((int)GetDifficulty() > 0)
					SetDifficulty(GetDifficulty() - 1);
				else
					SetDifficulty(Impossible);
			}
			if (IsKeyPressed(KEY_SPACE))
			{
				mState = Starting;
				SetMoveSpeed();
			}
		}

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}