#ifndef ENGINEIMPL_RENDERER_HPP
#define ENGINEIMPL_RENDERER_HPP

#include "Defines.hpp"
#include "raylib.h"

struct Texture;
struct Color;
struct Rectangle;

namespace render 
{
	void BeginDraw();
	void ClearScreen();
	void EndDraw();
	GAPI void DrawTexture(Texture texture2D, i32 x, i32 y, Color tint);
	GAPI void DrawSprite(Texture texture2D, Rectangle srcRect, Rectangle dstRect, Color tint, float rotation = 0);
}

#endif //ENGINEIMPL_RENDERER_HPP