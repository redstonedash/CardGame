void main() {
	Camera cam = { {0,1,0}, {0,0,0}, {0,0,-1}, CAMERA_ORTHOGRAPHIC };
	InitWindow(100, 100, "CardGame");
#include "CombatModual.h"
#include "BoardModual.h"
#include "UserIoModual.h"
#include "TimerModual.h"
	registerCardSystems();
	registerAttackSystem();
	registerActionIOSystems();
	registerTimerSystems();
	flecs::entity card1(world, "card1");
	card1.add<ActionToken>();
	card1.set<Card>({ 1, 2, 3, 4 });
	flecs::entity card2(world, "card2");
	card2.set<Card>({ 5, 6, 7, 8 });
	addCardToBoard({ 0,0 }, card1.id());
	addCardToBoard({ 1,4 }, card2.id());
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);
		BeginMode3D(cam);
		world.progress(0);
		EndMode3D();
		EndDrawing();
	}
}
