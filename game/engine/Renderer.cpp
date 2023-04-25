#include <cmath>
#include "Renderer.hpp"
#include "raylib.h"


namespace render 
{
	void BeginDraw() {
		BeginDrawing();
	}
	void ClearScreen() {
		ClearBackground(BLACK);
	}
	void EndDraw() {
		EndDrawing();
	}
	void DrawTexture(Texture texture, i32 x, i32 y, Color tint) {
		::DrawTexture(texture, x, y, tint);
	}
	void DrawSprite(Texture texture2D, Rectangle srcRect, Rectangle dstRect, Color tint, float rotation) {
		::DrawTexturePro(texture2D, srcRect, dstRect, { srcRect.width/2, srcRect.height / 2 }, rotation, tint);
	}

}