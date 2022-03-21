#include <iostream>
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

const Image w_icon = LoadImage("./data/images/aliens.png");
const int w_width = MY_GAME_WIDTH;
const int w_height = MY_GAME_HEIGHT;

Rectangle bob_rect;
Vector2 bob_post;

bool is_jumping = false;

/**
* @returns The time since last frame.
**/
const float DeltaTime() {
	return GetFrameTime();
}

const bool IsOnGround() {
	return (bob_post.y > (w_height - bob_rect.height));
}

const bool HasJumped() {
	return !is_jumping && (IsKeyPressed(KEY_SPACE));
}

int main() {
	using std::cout;
	using std::endl;

	// Accelaration due to gravity.
	// (P/S) / S == ((P)IXELS / (S)ECONDS) / (S)ECONDS
	const int gravity = 1000;
	const int jump_velocity = 600; // Pixels per second.

	int bob_velocity{}; // Declare & initialize to 0 using braced initialization.

	InitWindow(w_width, w_height, MY_GAME_TITLE);
	SetWindowIcon(w_icon);
	SetTargetFPS(60);

	const Texture2D bob = LoadTexture("./data/sprites/bob.png");

	bob_rect.x = (bob_rect.y = 0);
	bob_rect.width = (bob.width / 11);
	bob_rect.height = bob.height;

	bob_post.x = ((w_width / 2) - (bob_rect.width / 2));
	bob_post.y = (w_height - bob_rect.height);

	while (!WindowShouldClose()) {
		const float delta = DeltaTime();
		cout << delta << endl;

		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText("Hello, world!", ((w_width / 2) - 76), ((w_height / 2) - 10), 24, LIGHTGRAY);

		// Is the player on the ground?
		if (IsOnGround()) {
			bob_velocity = 0;
			bob_post.y = (w_height - bob_rect.height); // Bounce player position to be on the ground otherwise player might end up slightly through the ground. Maybe think about clamping the player's velocity?
			is_jumping = false;
		} else {
			// Player is in the air; apply gravity.
			bob_velocity = (bob_velocity + gravity * delta);
			is_jumping = true;
		}

		if (HasJumped()) {
			bob_velocity = (bob_velocity - jump_velocity);
		}

		// Update position.
		bob_post.y = (bob_post.y + bob_velocity * delta);

		DrawTextureRec(bob, bob_rect, bob_post, WHITE);

		EndDrawing();
	}

	UnloadImage(w_icon);
	UnloadTexture(bob);
	CloseWindow();

	return 0;
}
