#pragma once
#include "raylib.h"
#include <string>

enum Difficulty {
	Easy,
	Medium,
	Hard,
	Hardcore,
	Impossible,
};

int GetScore();
void SetScore(int score);
int GetSeconds();
int GetBestScore();
void SetBestScore(int score);
void SetSeconds(int value);
int GetDifficulty();
int GetStartingCounter();

void SetStartingCounter(int value);
void SetDifficulty(int value);

void DrawStartMenu();

void DrawLoseMenu();
void DrawTopMenu();
void DrawStartingMenu();

const int screenWidth = 704;
const int screenHeight = 754;