#include "raylib.h"

#define MY_GAME_TITLE "Aliens!"
#define MY_GAME_WIDTH 512
#define MY_GAME_HEIGHT 380

/**
 * Velocity finds speed of an object by its distance over time.
 * Say an alien moves 30 meters forward in 3 seconds. We can calculate the velocity of the alien using the formula below.
 * (V)ELOCITY = (D)ISTANCE / (T)IME
 * 
 * e.g. (30 / 3) = 10 == 10 = (30 / 3)
 **/

 /**
 * Gravity is a downwards force that pulls objects towards the ground and imparts an accelaration.
 * Velocity is change in position where as accelaration is change in velocity.
 * 
 * In free fall, all objects in real life accelarate at 9.8 m/s per second when falling towards the earth.
 * Meaning each second, the change in downwards velocity towards planet earth increases 9.8 meters every second.
 * 
 * (A)CCELARATION = (㎧)/s
 * (F)ORCE = (M)ASS * (A)CCELARATION
 **/

const int width = MY_GAME_WIDTH;
const int height = MY_GAME_HEIGHT;

const int player_width = 32;
const int player_height = 32;

int player_x = ((width / 2) - (player_width / 2));
int player_y = (height - player_height);

bool is_jumping;

const bool IsOnGround();
const bool HasJumped();

int main() {
	// Accelaration due to gravity.
	// (P/F) / F == ((P)IXELS / (F)RAME) / (F)RAME
	const int gravity = 1;
	const int jump_velocity = 16;

	int player_velocity{}; // Declare & initialize to 0 using braced initialization.

	InitWindow(width, height, MY_GAME_TITLE);
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText("Hello, world!", ((width / 2) - 76), ((height / 2) - 10), 24, LIGHTGRAY);

		// Is the player on the ground?
		if (IsOnGround()) {
			player_velocity = 0;
			is_jumping = false;
		}
		else {
			// Player is in the air; apply gravity.
			player_velocity = (player_velocity + gravity);
			is_jumping = true;
		}

		if (HasJumped()) {
			player_velocity = (player_velocity - jump_velocity);
		}

		// Update position.
		player_y = (player_y + player_velocity);

		DrawRectangle(player_x, player_y, player_width, player_height, BLACK);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

const bool IsOnGround() {
	return (player_y >= (height - player_height));
}

const bool HasJumped() {
	return !is_jumping && (IsKeyPressed(KEY_SPACE));
}
