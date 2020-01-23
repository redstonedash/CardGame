////////////////////////STRUCTS AND STUFF////////////////////////

////////////////////////COMPONENTS//////////////////////
flecs::component<Attack> Attack_c(world, "Attack");
flecs::component<Side> Side_c(world, "Side");
flecs::component<Health> Health_c(world, "Health");

////////////////////////SYSTEMS////////////////////////

flecs::system<Card, Attack> AttackSystem_s(world, "AttackSystem");
auto registerAttackSystem = [&]() {
	AttackSystem_s.kind(flecs::Manual);
	AttackSystem_s.action([&](flecs::rows rows, flecs::column<Card> card, flecs::column<Attack> attack) {
		for (auto row : rows) {
			Health * hlth = flecs::entity(world, attack[row].target).get_ptr<Health>();
			hlth->health -= attack[row].damage;
			rows.entity(row).remove<Attack>();
			rows.entity(row).set<Timer>({ (float) card->BAT });
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