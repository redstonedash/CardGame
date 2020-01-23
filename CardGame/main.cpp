void main() {
	Camera cam = { {0,1,0}, {0,0,0}, {0,0,-1}, CAMERA_ORTHOGRAPHIC };
	InitWindow(100, 100, "CardGame");
#include "CombatModual.h"
#include "BoardModual.h"
#include "UserIoModual.h"
	registerCardSystems();
	registerAttackSystem();
	registerActionIOSystems();
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);
		BeginMode3D(cam);
		world.progress(0);
		EndMode3D();
		EndDrawing();
	}
}