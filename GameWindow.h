#pragma once

#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include "raylib.h"

#define MY_GAME_TITLE "Aliens!"
#define MY_GAME_WIDTH 512
#define MY_GAME_HEIGHT 380

struct Window {
	const Image icon = LoadImage("./data/images/aliens.png");
	const int height{MY_GAME_HEIGHT};
	const int width{MY_GAME_WIDTH};
	const char w_title[9]{MY_GAME_TITLE};
} const window;

#endif
