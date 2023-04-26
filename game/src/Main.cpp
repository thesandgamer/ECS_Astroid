/*******************************************************************************************
*
*   raylib game template
*
*   <Game title>
*   <Game description>
*
*   This game has been created using raylib (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2021 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "../engine/Engine.hpp"
#include "game/Game.hpp"



//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{

    Engine engine;
    engine.Start(WINDOW_WIDTH, WINDOW_HEIGHT,"ECS implementation", std::make_unique<Game>());

    return 0;
}
