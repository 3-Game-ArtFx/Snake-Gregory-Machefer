#include "raylib.h"
#include <vector>

//std::vector<Vector2> mPlayerPos;
//std::vector<int> mPlayerPos;
std::vector<int> mPlayerPos;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main2(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Black'n White Snake");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Texture2D bloc = LoadTexture("Default/tile_0009.png");

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Snake", 190, 200, 20, LIGHTGRAY);
        Vector2 vec;
        vec.x = 32;
        vec.y = 32;
        //DrawTexture(bloc, screenWidth/2 - bloc.width/2, screenHeight/2 - bloc.height/2, WHITE);
        DrawTextureEx(bloc, vec, 0, 2, WHITE);
       
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}