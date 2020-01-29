////////////////////////STRUCTS AND STUFF////////////////////////

////////////////////////COMPONENTS//////////////////////
flecs::component<Attack> Attack_c(world, "Attack");
flecs::component<Health> Health_c(world, "Health");
////////////////////////ENTITIES////////////////////////


////////////////////////SYSTEMS////////////////////////
flecs::system<Event> EventItterator_s(world, "EventItterator");
flecs::system<Event, Attack> AttackSystem_s(world, "AttackSystem");
flecs::system<Health> DieSystem_s(world, "DieSystem");

auto registerAttackSystem = [&]() {
	EventItterator_s.action([&](flecs::rows rows, flecs::column<Event> e){
		for (auto row : rows) {
			e[row].timeElapsed += rows.delta_time();
			e[row].framesElapsed++;
			//if (e[row].eventFunction) { how do memory safe
			//	e[row].eventFunction(e[row].timeElapsed, e[row].framesElapsed);
			//}
		}
	});
	AttackSystem_s.kind(flecs::PostUpdate);
	AttackSystem_s.action([&](flecs::rows rows, flecs::column<Event> e, flecs::column<Attack> attack) {
		for (auto row : rows) {
			int hp = flecs::entity(world, attack[row].target).get<Health>().health;
			hp -= attack[row].damage;
			flecs::entity(world, attack[row].target).set<Health>({ hp });
			auto e = flecs::entity(world, attack[row].attacker);
			e.set<Timer>({ e.get<Card>().BAT });
			rows.entity(row).remove<Attack>();
			rows.entity(row).remove<Event>();
		}
	});	
	DieSystem_s.kind(flecs::OnRemove);
	DieSystem_s.action([&](flecs::rows rows, flecs::column<Health> health) {
		for (auto row : rows) {
			if (health[row].health <= 0) {
				Vec2 me = FindMe(rows.entity(row).id());
				rows.entity(row).remove<Health>();
				if (me.x == 0) {
					Board[me.x][me.y] = Face0_e.id();
				} else {
					Board[me.x][me.y] = Face1_e.id();
				}
			}
		}
	});
};	