
void main() {
	Camera cam = { {0,1,0}, {0,0,0}, {0,0,-1}, 10, CAMERA_ORTHOGRAPHIC };
	InitWindow(1280, 720, "Armageddon");
	world.set_target_fps(60);
	SetTargetFPS(60);
#include "CombatModual.h"
#include "BoardModual.h"
#include "UserIoModual.h"
#include "TimerModual.h"
#include "CardInitModual.h"
#include "BoardDrawModual.h"
	initParalax();
	cardModel = LoadModel("resources/Card.glb");
	registerDrawCardSystem();
	registerInitCardSystems();
	registerAttackSystem();
	registerActionIOSystems();
	registerTimerSystems();

	auto HyenaAssets = LoadCardVisuals("hyena");
	auto FireGolemAssets = LoadCardVisuals("FireGolem");
	auto StoneGolemAssets = LoadCardVisuals("StoneGolem");
	HyenaAssets.thickness = 0.05f;
	FireGolemAssets.thickness = 0.05f;
	StoneGolemAssets.thickness = 0.05f;

	flecs::entity card1(world, "card1");
	card1.set<Card>({ 1, 2, 3, 4 }).set(HyenaAssets);
	//card1.add<ActionToken>(); //somone needs it 2:01
	flecs::entity card2(world, "card2");
	card2.set<Card>({5, 6, 7, 8 }).set(FireGolemAssets);
	flecs::entity card3(world, "card3");
	card3.set<Card>({5, 6, 7, 8 }).set(FireGolemAssets);
	flecs::entity card4(world, "card4");
	card4.set<Card>({5, 6, 7, 8 }).set(FireGolemAssets);
	flecs::entity card5(world, "card5");
	card5.set<Card>({5, 6, 7, 8 }).set(StoneGolemAssets);
	flecs::entity card6(world, "card6");	
	card6.set<Card>({1, 2, 3, 4 }).set(StoneGolemAssets);
	flecs::entity card8(world, "card8");	
	card8.set<Card>({5, 6, 7, 8 }).set(StoneGolemAssets);
	flecs::entity card9(world, "card9");
	card9.set<Card>({5, 6, 7, 8 }).set(StoneGolemAssets);
	flecs::entity card10(world, "card10");
	card10.set<Card>({5, 6, 7, 8 }).set(StoneGolemAssets);
	addCardToBoard({ 0,0 }, card1.id());
	addCardToBoard({ 0,1 }, card2.id());
	addCardToBoard({ 0,2 }, card3.id());
	addCardToBoard({ 0,3 }, card4.id());
	addCardToBoard({ 0,4 }, card5.id());
	addCardToBoard({ 1,0 }, card6.id());
	addCardToBoard({ 1,2 }, card8.id());
	addCardToBoard({ 1,3 }, card9.id());
	addCardToBoard({ 1,4 }, card10.id());
	BeginDrawing();
	BeginMode3D(cam);
	TimerSystem_s.run(0);
	EndMode3D();
	EndDrawing();
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(GRAY);
		BeginMode3D(cam);
		world.progress(0);
		EndMode3D();
		DrawCardInfoSystem_s.run();
		flecs::entity(world, gameJamMoment).remove<Attack>().remove<ActionToken>();
		EndDrawing();
	}
}
