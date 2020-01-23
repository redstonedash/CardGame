#include "CombatModual.hpp"

////////////////////////STRUCTS AND STUFF////////////////////////
struct Attack {
	flecs::entity_t target;
	int damage;
};

struct Vec2 {
	int x;
	int y;
};

flecs::entity HandP1[10];
flecs::entity HandP2[10];
flecs::entity_t Board[2][5];

auto FindMe = [&](flecs::entity_t id) -> Vec2 {
	int i = 0;
	int j = 0;
	for (; id != Board[i][j]; j++) {
		if (j >= 5) {
			j = 0;
			i = 1;
		}
	}
	return { i, j };
};

auto TargetsExist = [&](flecs::entity_t id) -> TargetInfo {
	Vec2 data = FindMe(id);
	bool isP1, isEdge;
	TargetInfo returnData = { false, false };

	if (data.x == 0) isP1 = true;
	if (data.y == 0) isEdge = true;

	if (isP1) {
		if (!isEdge) {
			if (Board[1][5 - data.y] != 0) returnData.leftTargetExists = true;
		}
		if (Board[1][5 - data.y - 1] != 0) returnData.rightTargetExists = true;
	}
	else {
		if (!isEdge) {
			if (Board[0][5 - data.y] != 0) returnData.leftTargetExists = true;
		}
		if (Board[0][5 - data.y - 1] != 0) returnData.rightTargetExists = true;
	}
	return returnData;
};

////////////////////////COMPONENTS//////////////////////
flecs::component<Attack> Attack_c(world, "Attack");
flecs::component<Side> Side_c(world, "Side");

////////////////////////SYSTEMS////////////////////////

flecs::system<Card, Side, Attack> AttackSystem_s(world, "AttackSystem");
auto registerAttackSystem = [&]() {
	AttackSystem_s.kind(flecs::Manual);
	AttackSystem_s.action([&](flecs::rows rows, flecs::column<Attack> attack) {
		for (auto row : rows) {
			auto atk = attack[row];
			auto hlth = atk.target.get<Health>();


		}
	});
	//AttackSystem_s.run(0, buf);
	//byte buf[sizeof(flecs::entity_t) + sizeof(flecs::entity_t)];
	//
	//flecs::entity_t attacker = 0;
	//*((flecs::entity_t*)buf[0]) = attacker;
	//*((flecs::entity_t*)buf[1]) = attacker;
	//
	//
	//auto attacker1 = ((flecs::entity_t*)rows.param())[0];
	//auto target = ((flecs::entity_t*)rows.param())[1];
};

////////////////////////ENTITIES////////////////////////

///////////////////////FUNCTIONS///////////////////////