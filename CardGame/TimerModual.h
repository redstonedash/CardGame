////////////////////////STRUCTS AND VARIABLES////////////////////////


////////////////////////COMPONENTS////////////////////////
flecs::component<Timer> Timer_c(world, "Timer");
////////////////////////SYSTEMS////////////////////////
flecs::system<Timer> TimerSystem_s(world, "TimerSystem");
auto registerTimerSystems = [&]() {
	TimerSystem_s.kind(flecs::Manual);
	TimerSystem_s.action([&](flecs::rows rows, flecs::column<Timer> t) {
		
		float min = -1.0;
		flecs::entity nextTurn = flecs::entity();
		for (auto row : rows) {
			if (t[row].time < min || min<0) {
				min = t[row].time;
				nextTurn = rows.entity(row);
			}
			//printf("%" PRId64 ": %f \n", rows.entity(row).id(), t[row].time);
		}
		//printf("END BOARD\n");
		//printf("%" PRId64 " %f \n", nextTurn.id(), min);
		//printf("//////////////////////////");
		nextTurn.add<ActionToken>();
		nextTurn.remove<Timer>();
		for (auto row : rows) {
			t[row].time -= min; //advance time based on how much time it takes to finish the next attack, will never result in negatives
		}
	});
};
////////////////////////ENTITIES////////////////////////
auto registerTimerEntities = [&]() {
};