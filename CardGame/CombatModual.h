////////////////////////STRUCTS AND STUFF////////////////////////
struct Attack {
	bool isLeft;
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

			int i = 0;

			if (sde.isP1) {
				while (rows.entity(row).id() != Board[0][i].id()) {
					i++;
				}
			}
			else {
				while (rows.entity(row).id() != Board[1][i].id()) {
					i++;
				}
			}
		}
	});
};

////////////////////////ENTITIES////////////////////////

///////////////////////FUNCTIONS///////////////////////

TargetInfo TargetsExist() {

}

int FindMe() {

}