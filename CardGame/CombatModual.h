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
	AttackSystem_s.action([&](flecs::rows rows, flecs::column<Card> card, flecs::column<Attack> attack) {
		for (auto row : rows) {
			auto atk = attack[row];
			auto crd = card[row];
		}
	});
}

////////////////////////ENTITIES////////////////////////
