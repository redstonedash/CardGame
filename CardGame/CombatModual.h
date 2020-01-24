////////////////////////STRUCTS AND STUFF////////////////////////

////////////////////////COMPONENTS//////////////////////
flecs::component<Attack> Attack_c(world, "Attack");
flecs::component<Side> Side_c(world, "Side");
flecs::component<Health> Health_c(world, "Health");

////////////////////////SYSTEMS////////////////////////

flecs::system<Card, Attack> AttackSystem_s(world, "AttackSystem");
auto registerAttackSystem = [&]() {
	AttackSystem_s.kind(flecs::PostUpdate);
	AttackSystem_s.action([&](flecs::rows rows, flecs::column<Card> card, flecs::column<Attack> attack) {
		for (auto row : rows) {
			Attack atk = attack[row];
			if (atk.target == 0) {
				//TODO get hp of face, we don't have a face yet
			}
			else {
				Health * hlth = flecs::entity(world, attack[row].target).get_ptr<Health>();
				printf("%d -> ", hlth->health);
				hlth->health -= attack[row].damage;
				printf("%d\n", hlth->health); //warning these are pointers and they might die when we do stuff with flecs
				//rows.entity(row).remove<Attack>(); game jam moment
				//rows.entity(row).remove<ActionToken>(); //1:59 just keeping track of time, that way tommarow i can just look at the latest stuff and it will probably need review first
				gameJamMoment = rows.entity(row).id();
				rows.entity(row).set<Timer>({ card[row].BAT });
			}
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