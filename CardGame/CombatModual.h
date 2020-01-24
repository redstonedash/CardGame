////////////////////////STRUCTS AND STUFF////////////////////////

////////////////////////COMPONENTS//////////////////////
flecs::component<Attack> Attack_c(world, "Attack");
flecs::component<Side> Side_c(world, "Side");
flecs::component<Health> Health_c(world, "Health");
////////////////////////ENTITIES////////////////////////


////////////////////////SYSTEMS////////////////////////

flecs::system<Card, Attack> AttackSystem_s(world, "AttackSystem");
flecs::system<Health> DieSystem_s(world, "DieSystem");
auto registerAttackSystem = [&]() {
	AttackSystem_s.kind(flecs::PostUpdate);
	DieSystem_s.kind(flecs::OnRemove);//TO CARTER IMPLIMENT THIS SYSTEM, IT DO THIS ecs_delete(world.c_ptr(), ((ecs_entity_t)flecs::entity(world, attack[row].target).id()));
	AttackSystem_s.action([&](flecs::rows rows, flecs::column<Card> card, flecs::column<Attack> attack) {
		for (auto row : rows) {
			if (row != 0) {
				printf("why");
			}
			Attack atk = attack[row];
			if (atk.target == 0) {
				//Health * hlth = Face_e.get_ptr<Health>();
				//printf("ATTACKING FACE %d -> ", hlth->health);
				//hlth->health -= attack[row].damage;
				////if (hlth->health <= 0) {
				////	//WinGameJam();
				////}
			}
			else {
				Health * hlth = flecs::entity(world, attack[row].target).get_ptr<Health>();
				printf("%d -> ", hlth->health);
				hlth->health -= attack[row].damage;
				if (hlth->health <= 0) {
					flecs::entity(world, attack[row].target).remove<Health>();
				}
				printf("%d\n", hlth->health); //warning these are pointers and they might die when we do stuff with flecs
				//rows.entity(row).remove<Attack>(); game jam moment
				//rows.entity(row).remove<ActionToken>(); //1:59 just keeping track of time, that way tommarow i can just look at the latest stuff and it will probably need review first
				rows.entity(row).set<Timer>({ card[row].BAT });
			}
			gameJamMoment = rows.entity(row).id();
		}

	});

	DieSystem_s.action([&](flecs::rows rows, flecs::column<Health> health) {
		for (auto row : rows) {
			flecs::entity_t id = rows.entity(row).id();
			ecs_delete(world.c_ptr(), ((ecs_entity_t)rows.entity(row).id()));
			Vec2 me = FindMe(id);
			Board[me.x][me.y] = 0;
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