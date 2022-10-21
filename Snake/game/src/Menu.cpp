#include "Menu.h"
#include "Grid.h"

int mScore = 0;
int mSecond = 0;
int mBestScore = 0;
int mDifficulty = Hard;
int mStartingCounter = 3;

#pragma region GET SET

int GetStartingCounter()
{
	return mStartingCounter;
}

void SetStartingCounter(int value)
{
	mStartingCounter = value;
}

int GetDifficulty() 
{
	return mDifficulty;
}

void SetDifficulty(int value) 
{
	mDifficulty = value;
}

int GetSeconds() {
	return mSecond;
}

void SetSeconds(int value) 
{
	mSecond = value;
}

int GetScore() 
{
	return mScore;
}

void SetScore(int score) 
{
	mScore = score;
}

int GetBestScore()
{
	return mBestScore;
}

void SetBestScore(int score) 
{
	mBestScore = score;
}

#pragma endregion

/// <summary>
/// Draw lose menu
/// </summary>
void DrawLoseMenu()
{
	DrawRectangle(0, 0, screenWidth, screenHeight, CLITERAL(Color){ 0, 0, 0, 100 });
	std::string loseText = "You lose!";
	int textSize = MeasureText(loseText.c_str(), 40);
	DrawText(loseText.c_str(), screenWidth / 2 - textSize / 2, 280, 40, WHITE);

	std::string loseScoreText = "Your score: " + std::to_string(mScore);
	textSize = MeasureText(loseScoreText.c_str(), 40);
	DrawText(loseScoreText.c_str(), screenWidth / 2 - textSize / 2, 320, 40, WHITE);

	std::string restartText = "Press SPACE";
	textSize = MeasureText(restartText.c_str(), 40);
	DrawText(restartText.c_str(), screenWidth / 2 - textSize / 2, 400, 40, WHITE);
}

/// <summary>
/// Draw to menu (score, best score, timer)
/// </summary>
void DrawTopMenu() 
{
	DrawRectangle(0, 0, 800, Y_GRID_OFFSET, CLITERAL(Color){ 20, 20, 20, 255 });
	std::string scoreText = "Score " + std::to_string(GetScore());
	DrawText(scoreText.c_str(), 4, 3, 20, WHITE);

	std::string bestScoreText = "Best score " + std::to_string(mBestScore);
	DrawText(bestScoreText.c_str(), 4, 26, 20, WHITE);

	std::string timeText = "Time " + std::to_string(mSecond);
	int textSize = MeasureText(timeText.c_str(), 20);
	DrawText(timeText.c_str(), screenWidth / 2 - textSize / 2, 26, 20, WHITE);
}

/// <summary>
/// Draw the main start menu
/// </summary>
void DrawStartMenu()
{
	DrawRectangle(0, 0, screenWidth, screenHeight, CLITERAL(Color){ 0, 0, 0, 150 });

	std::string restartText = "Press SPACE to start";
	int textSize = MeasureText(restartText.c_str(), 40);
	DrawText(restartText.c_str(), screenWidth / 2 - textSize / 2, 440, 40, WHITE);
	std::string difficultyText = "Difficulty: ";
	switch (mDifficulty)
	{
	case Easy:
		difficultyText += "Easy";
		break;
	case Medium:
		difficultyText += "Medium";
		break;
	case Hard:
		difficultyText += "Hard";
		break;
	case Hardcore:
		difficultyText += "Hardcore";
		break;
	case Impossible:
		difficultyText += "Impossible";
		break;
	}

	textSize = MeasureText(difficultyText.c_str(), 35);
	DrawText(difficultyText.c_str(), screenWidth / 2 - textSize / 2, 500, 35, WHITE);

	std::string difficultyChangeText = "(Change with arrows)";
	textSize = MeasureText(difficultyChangeText.c_str(), 25);
	DrawText(difficultyChangeText.c_str(), screenWidth / 2 - textSize / 2, 540, 25, WHITE);
}

/// <summary>
/// Draw the starting menu
/// </summary>
void DrawStartingMenu()
{
	std::string timerText = std::to_string(mStartingCounter);
	int ts1 = MeasureText(timerText.c_str(), 40);
	DrawText(timerText.c_str(), screenWidth / 2 - ts1 / 2, 300, 60, WHITE);
}