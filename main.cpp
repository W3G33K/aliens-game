#include <malloc.h>
#include "raylib.h"
#include "raymath.h"

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

struct Window {
	const Image icon = LoadImage("./data/images/aliens.png");
	const int height{MY_GAME_HEIGHT};
	const int width{MY_GAME_WIDTH};
	char w_title[9]{MY_GAME_TITLE};
} const window;

Rectangle bob_rect;
Vector2 bob_post;
Rectangle slime_rect;
Vector2 slime_post;

bool is_jumping = false;

/**
* @returns The time since last frame.
**/
const inline float DeltaTime() {
	return GetFrameTime();
}

/**
* @returns Is Bob on the ground?
**/
const bool IsOnGround() {
	return (bob_post.y >= (window.height - bob_rect.height));
}

/**
* @returns Has Bob jumped?
**/
const bool HasJumped() {
	return !is_jumping && (IsKeyDown(KEY_SPACE));
}

int main() {
	// Accelaration due to gravity.
	// (P/S) / S == ((P)IXELS / (S)ECONDS) / (S)ECONDS
	const int gravity = 1'000;
	const int jump_velocity = 600; // Pixels per second.
	const float update_time = (1.0f / 10.0f); // Update 10 times per second.
	float running_time{};

	int bob_frame{};
	int bob_velocity{}; // Declare & initialize to 0 using braced initialization.
	int slime_frame{};
	int slime_velocity = -300;

	InitWindow(window.width, window.height, window.w_title);
	SetWindowIcon(window.icon);
	SetTargetFPS(60);

	const Texture2D bob = LoadTexture("./data/sprites/bob.png");
	const Texture2D slime = LoadTexture("./data/sprites/slime.png");

	bob_rect.x = (bob_rect.y = 0);
	bob_rect.width = (bob.width / 11);
	bob_rect.height = bob.height;

	bob_post.x = ((window.width / 2) - (bob_rect.width / 2));
	bob_post.y = (window.height - bob_rect.height);

	slime_rect.x = (slime_rect.y = 0);
	slime_rect.width = (slime.width / 3);
	slime_rect.height = slime.height;

	slime_post.x = (window.width + slime_rect.width);
	slime_post.y = (window.height - slime_rect.height);

	while (!WindowShouldClose()) {
		const float delta = DeltaTime();

		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText("Hello, world!", ((window.width / 2) - 76), ((window.height / 2) - 10), 24, LIGHTGRAY);

		// Is the player on the ground?
		if (IsOnGround()) {
			is_jumping = false;
			bob_velocity = 0;
			bob_post.y = (window.height - bob_rect.height); // Bounce player position to be on the ground just incase?
		} else {
			// Player is in the air; apply gravity.
			is_jumping = true;
			bob_velocity = (bob_velocity + gravity * delta);
		}

		if (HasJumped()) {
			is_jumping = true;
			bob_velocity = (bob_velocity - jump_velocity);
		}

		// Update position.
		bob_post.y = Clamp((bob_post.y + bob_velocity * delta), 0.0f, (window.height - bob_rect.height));
		slime_post.x = (slime_post.x + slime_velocity * delta);
		if (slime_post.x < -slime_rect.width) {
			slime_post.x = (window.width + slime_rect.width);
		}

		// Update Bob's animation frame.
		running_time = (running_time + delta);
		if (running_time >= update_time) {
			running_time = 0.0f;
			if (!IsOnGround()) {
				bob_frame = 5;
			}

			bob_rect.x = (bob_frame * bob_rect.width);
			bob_frame = (bob_frame + 1);
			if (bob_frame > 10) {
				bob_frame = 0;
			}

			slime_rect.x = (slime_frame * slime_rect.width);
			slime_frame = (slime_frame + 1);
			if (slime_frame > 2) {
				slime_frame = 0;
			}
		}

		DrawTextureRec(bob, bob_rect, bob_post, WHITE);
		DrawTextureRec(slime, slime_rect, slime_post, WHITE);

		EndDrawing();
	}

	UnloadImage(window.icon);
	UnloadTexture(bob);
	UnloadTexture(slime);
	CloseWindow();

	return 0;
}
