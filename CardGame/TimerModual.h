////////////////////////STRUCTS AND VARIABLES////////////////////////
struct Timer {
	float time;
};

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
			if (min < t[row].time || min<0) {
				float min = t[row].time;
				flecs::entity nextTurn = rows.entity(row);
			}
		}
		nextTurn.add<

	});
};
////////////////////////ENTITIES////////////////////////
auto registerTimerSystems = [&]() {
	flecs::entity gameObject1_e(world, "gameObject1");
	gameObject1_e.set<Card>({ 5 });
};