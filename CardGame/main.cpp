#include "BoardDrawModual.h"

void main() {
	Camera cam = { {0,1,0}, {0,0,0}, {0,0,-1}, CAMERA_ORTHOGRAPHIC };
	InitWindow(1280, 720, "CardGame");
#include "CombatModual.h"
#include "BoardModual.h"
#include "UserIoModual.h"
#include "TimerModual.h"
	registerCardSystems();
	registerAttackSystem();
	registerActionIOSystems();
	registerTimerSystems();
	registerTimerEntities();
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);
		BeginMode3D(cam);
		world.progress(0);
		EndMode3D();
		EndDrawing();
	}
}
