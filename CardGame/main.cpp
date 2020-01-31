#include <thread>
#include <mutex>
void lock(ecs_os_mutex_t mutex) {
	((std::mutex*)mutex)->lock();
}
ecs_os_mutex_t newMutex() {
	std::mutex* mutex = new std::mutex;
	return (uintptr_t)mutex;
}
void mutexFree(ecs_os_mutex_t mutex) {
	delete(((std::mutex*)mutex));
}
void unlock(ecs_os_mutex_t mutex) {
	((std::mutex*)mutex)->unlock();
}
ecs_os_thread_t newThread(ecs_os_thread_callback_t callback,
	void *param) {
	std::thread * thread = new std::thread(callback, param);
	return (ecs_os_thread_t)param;
}
void main() {
	Camera cam = { {0,1,0}, {0,0,0}, {0,0,-1}, 10, CAMERA_ORTHOGRAPHIC };
	InitWindow(1280, 720, "Armageddon");
	world.set_target_fps(60);
	ecs_os_set_api_defaults();
	ecs_os_api_t os_api = ecs_os_api;
	
	ecs_os_api.mutex_lock = lock;
	ecs_os_api.mutex_new = newMutex;
	ecs_os_api.mutex_free = mutexFree;
	ecs_os_api.mutex_unlock = unlock;
	ecs_os_api.thread_new = newThread;
	ECS_IMPORT(world.c_ptr(), FlecsSystemsConsole, 0);
	ecs_set(world.c_ptr(), 0, EcsConsole, { 0 });
	SetTargetFPS(60);
	flecs::entity Face0_e = flecs::entity(world, "Face0").add<Health>();//.add<Hand>();
	flecs::entity Face1_e = flecs::entity(world, "Face1").add<Health>();//.add<Hand>();
	//ECS_IMPORT(world.c_ptr(), FlecsSystemsConsole, 0);
	//ecs_set(world.c_ptr(), 0, EcsConsole, { 0 });
#include "CombatModual.h"
#include "BoardModual.h"
#include "TurnHandlerModual.h"
#include "CardInitModual.h"
#include "BoardDrawModual.h"
#include "flecs_systems_console.h"
	initParalax();
	cardModel = LoadModel("resources/Card.glb");
	registerDrawCardSystem();
	registerInitCardSystems();
	registerAttackSystem();
	registerTurnHandlerSystems();

	auto HyenaAssets = LoadCardVisuals("hyena");
	auto FireGolemAssets = LoadCardVisuals("FireGolem");
	auto StoneGolemAssets = LoadCardVisuals("StoneGolem");
	HyenaAssets.thickness = 0.05f;
	FireGolemAssets.thickness = 0.05f;
	StoneGolemAssets.thickness = 0.05f;

	vignette = LoadTexture("resources/vignette.png");
	flecs::entity card1(world, "card1");
	card1.set<Card>({ 160, 200, 300, 160, 100 }).set(HyenaAssets);
	//card1.add<ActionToken>(); //somone needs it 2:01
	flecs::entity card2(world, "card2");
	card2.set<Card>({5, 6, 7, 8, 1 }).set(FireGolemAssets);
	flecs::entity card3(world, "card3");
	card3.set<Card>({5, 6, 7, 8, 1 }).set(FireGolemAssets);
	flecs::entity card4(world, "card4");
	card4.set<Card>({5, 6, 7, 8, 1 }).set(FireGolemAssets);
	flecs::entity card5(world, "card5");
	card5.set<Card>({5, 6, 7, 8, 1 }).set(StoneGolemAssets);
	flecs::entity card6(world, "card6");	
	card6.set<Card>({1, 2, 3, 4, 1 }).set(StoneGolemAssets);
	flecs::entity card8(world, "card8");	
	card8.set<Card>({5, 6, 7, 8, 1 }).set(StoneGolemAssets);
	flecs::entity card9(world, "card9");
	card9.set<Card>({5, 6, 7, 8, 1 }).set(StoneGolemAssets);
	flecs::entity card10(world, "card10");
	card10.set<Card>({5, 6, 7, 8, 1 }).set(StoneGolemAssets);
	addCardToBoard({ 0,0 }, card1.id());
	addCardToBoard({ 0,1 }, card2.id());
	addCardToBoard({ 0,2 }, card3.id());
	addCardToBoard({ 0,3 }, card4.id());
	addCardToBoard({ 0,4 }, card5.id());
	addCardToBoard({ 1,0 }, Face1_e.id());
	addCardToBoard({ 1,1 }, Face1_e.id());
	addCardToBoard({ 1,2 }, Face1_e.id());
	addCardToBoard({ 1,3 }, Face1_e.id());
	addCardToBoard({ 1,4 }, Face1_e.id());
	BeginDrawing();
	BeginMode3D(cam);
	TimerSystem_s.run(0);
	EndMode3D();
	EndDrawing();
	while (!WindowShouldClose()) {
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			BeginDrawing();
		} else {
			BeginDrawing();
		}
		ClearBackground(GRAY);
		DrawTexture(vignette, 0, 0, WHITE);
		BeginMode3D(cam);
		BlockInputSystem_s.run();
		world.progress(0);
		EndMode3D();
		DrawCardInfoSystem_s.run();
		bool a = false;
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			EndDrawing();
		} else {
			EndDrawing();
		}
		
	}
}
