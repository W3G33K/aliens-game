#include <iostream>
#include "raylib.h"

#define MY_GAME_TITLE "Aliens!"
#define MY_GAME_WIDTH 512
#define MY_GAME_HEIGHT 380

int main() {
	using std::cout;
	using std::endl;
	cout << "Hello, world!" << endl;

	const int width = MY_GAME_WIDTH;
	const int height = MY_GAME_HEIGHT;

	InitWindow(width, height, MY_GAME_TITLE);
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Hello, world!", ((width / 2) - 76), ((height / 2) - 10), 24, LIGHTGRAY);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
