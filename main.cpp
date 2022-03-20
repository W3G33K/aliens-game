#include "raylib.h"

#define MY_GAME_TITLE "Aliens!"
#define MY_GAME_WIDTH 512
#define MY_GAME_HEIGHT 380

/**
 * Velocity finds speed of an object by its distance over time.
 * Say an alien moves 30 meters forward in 3 seconds. We can calculate the velocity of the alien using the formula below.
 * V = D / T
 * 
 * (e.g. 30 / 3 = 10 | 10 = 30 / 3)
 **/

int main() {
	const int width = MY_GAME_WIDTH;
	const int height = MY_GAME_HEIGHT;

	const int player_width = 32;
	const int player_height = 32;

	int player_velocity{}; // Declare and initialize to 0 with braced initialization.
	int player_x = ((width / 2) - (player_width / 2));
	int player_y = (height - player_height);

	InitWindow(width, height, MY_GAME_TITLE);
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Hello, world!", ((width / 2) - 76), ((height / 2) - 10), 24, LIGHTGRAY);
		if (IsKeyPressed(KEY_SPACE)) {
			player_velocity = (player_velocity - 8);
		}

		player_y = (player_y + player_velocity);

		DrawRectangle(player_x, player_y, player_width, player_height, BLACK);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
