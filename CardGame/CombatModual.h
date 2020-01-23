////////////////////////STRUCTS AND STUFF////////////////////////
struct Attack {
	bool isLeft;
};

struct Vec2 {
	int x;
	int y;
};

flecs::entity HandP1[10];
flecs::entity HandP2[10];
flecs::entity Board[2][5];

////////////////////////COMPONENTS//////////////////////
flecs::component<Attack> Attack_c(world, "Attack");


////////////////////////SYSTEMS////////////////////////

flecs::system<Card, Attack> AttackSystem_s(world, "AttackSystem");
auto registerAttackSystem = [&]() {
	AttackSystem_s.action([&](flecs::rows rows, flecs::column<Card> card, flecs::column<Side> side, flecs::column<Attack> attack) {
		for (auto row : rows) {
			auto crd = card[row];
			auto sde = side[row];
			auto atk = attack[row];



		}
	});
};

////////////////////////ENTITIES////////////////////////

///////////////////////FUNCTIONS///////////////////////

auto FindMe = [](flecs::entity_t id) -> Vec2 {
	int i = 0;
	int j = 0;
	for (; id != Board[i][j].id(); j++) {
		if (j >= 5) {
			j = 0;
			i = 1;
		}
	}
	return { i, j };
};

auto TargetsExist = [](flecs::entity_t id) -> TargetInfo {
	Vec2 data = FindMe(id);
	bool isP1, isEdge;
	TargetInfo returnData = {false, false};

	if (data.x == 0) isP1 = true;
	if (data.y == 0) isEdge = true;

	if (isP1) {
		if (!isEdge) {
			
		}
	}
};