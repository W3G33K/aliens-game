#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "raylib.h"

struct Entity {
	Texture2D sprite;
	Rectangle bounds;
	Vector2 position;
	bool is_jumping;
	int frame;
	int jump_frame;
	int total_frames;
	int x_velocity;
	int y_velocity;
	int jump_velocity;
	float running_time;
	float update_time;
};

#endif
