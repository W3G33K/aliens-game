#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "raymath.h"

#include "GameWindow.h"
#include "Entity.h"
#include "Bob.h"
#include "Slime.h"

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

/**
* @returns The time since last frame.
**/
const inline float DeltaTime() {
	return GetFrameTime();
}

/**
* @returns Is Bob on the ground?
**/
const bool IsOnGround(Bob *bob) {
	return (bob->position.y >= (window.height - bob->bounds.height));
}

/**
* @returns Has Bob jumped?
**/
const bool HasJumped(Bob *bob) {
	return (!bob->is_jumping && (IsKeyDown(KEY_SPACE)));
}

const void UpdateAnimation(Entity *entity) {
	entity->running_time = (entity->running_time + DeltaTime());
	if (entity->running_time >= entity->update_time) {
		entity->running_time = 0.0f;
		if (entity->is_jumping) {
			entity->frame = entity->jump_frame;
		}

		entity->bounds.x = (entity->frame * entity->bounds.width);
		entity->frame = (entity->frame + 1);
		if (entity->frame > (entity->total_frames - 1)) {
			entity->frame = 0;
		}
	}
}

int main() {
	srand(time(NULL));

	// Accelaration due to gravity.
	// (P/S) / S == ((P)IXELS / (S)ECONDS) / (S)ECONDS
	const int gravity = 1'000;

	InitWindow(window.width, window.height, window.w_title);
	SetWindowIcon(window.icon);
	SetTargetFPS(60);

	Bob bob;
	bob.sprite = LoadTexture("./data/sprites/bob.png");
	bob.bounds.x = (bob.bounds.y = 0);
	bob.bounds.width = (bob.sprite.width / 11);
	bob.bounds.height = bob.sprite.height;
	bob.position.x = ((window.width / 2) - (bob.bounds.width / 2));
	bob.position.y = (window.height - bob.bounds.height);
	bob.jump_frame = 5;
	bob.total_frames = 11;
	bob.x_velocity = 0;
	bob.y_velocity = 600; // Pixels per second.
	bob.update_time = (1.0f / 12.0f); // Update 12 times per second.

	Slime slime;
	slime.sprite = LoadTexture("./data/sprites/slime.png");
	slime.bounds.x = (slime.bounds.y = 0);
	slime.bounds.width = (slime.sprite.width / 3);
	slime.bounds.height = slime.sprite.height;
	slime.position.x = (window.width + slime.bounds.width);
	slime.position.y = (window.height - slime.bounds.height);
	slime.jump_frame = 1;
	slime.total_frames = 3;
	slime.x_velocity = 300; // Pixels per second.
	slime.y_velocity = 0;
	slime.update_time = (1.0f / 4.0f); // Update 4 times per second.

	bob.frame = (slime.frame = 0);
	bob.is_jumping = (slime.is_jumping = false);
	bob.jump_velocity = (slime.jump_velocity = 600);
	bob.running_time = (slime.running_time = 0.0f);

	while (!WindowShouldClose()) {
		const float delta = DeltaTime();

		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText("Hello, world!", ((window.width / 2) - 76), ((window.height / 2) - 10), 24, LIGHTGRAY);

		// Is the player on the ground?
		if (IsOnGround(&bob)) {
			bob.is_jumping = false;
			bob.y_velocity = 0;
			bob.position.y = (window.height - bob.bounds.height); // Bounce player position to be on the ground just incase?
		} else {
			// Player is in the air; apply gravity.
			bob.is_jumping = true;
			bob.y_velocity = (bob.y_velocity + gravity * delta);
		}

		if (HasJumped(&bob)) {
			bob.is_jumping = true;
			bob.y_velocity = (bob.y_velocity - bob.jump_velocity);
		}

		// Update position.
		bob.position.y = Clamp((bob.position.y + (bob.y_velocity * delta)), 0.0f, (window.height - bob.bounds.height));
		slime.position.x = (slime.position.x - (slime.x_velocity * delta));
		if (slime.position.x < -slime.bounds.width) {
			slime.position.x = (window.width + slime.bounds.width);
		}

		// Update animation frames.
		UpdateAnimation(&bob);
		UpdateAnimation(&slime);

		DrawTextureRec(bob.sprite, bob.bounds, bob.position, WHITE);
		DrawTextureRec(slime.sprite, slime.bounds, slime.position, GREEN);

		EndDrawing();
	}

	UnloadImage(window.icon);
	UnloadTexture(bob.sprite);
	UnloadTexture(slime.sprite);
	CloseWindow();

	return 0;
}
