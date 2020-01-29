////////////////////////STRUCTS AND VARIABLES////////////////////////
bool EventsInProgresss = false;

////////////////////////COMPONENTS////////////////////////
flecs::component<Timer> Timer_c(world, "Timer");
flecs::component<Event> Event_c(world, "Event");
////////////////////////SYSTEMS////////////////////////
flecs::system<Timer> TimerSystem_s(world, "TimerSystem");
flecs::system<Event> BlockInputSystem_s(world, "BlockInputSystem");
//flecs::system<ActionToken> RunTimer_s(world, "RunTimer");
auto inputHandler = [](flecs::entity e) {
	Vec2 data = FindMe(e.id());
	Vector3 pos = { 0, 0, 0 };
	float spacing = 0.5f;
	if (data.x == 0) {
		pos = { data.y * (spacing * 5) - spacing - 5.0f, -100.f, 1.75f };
	}
	else {
		pos = { std::abs(data.y - 4) * (spacing * 5) + spacing - 5.0f, -100.f, -1.75f };
	}
	DrawCube(pos, 2.f, 0.1f, 3.5f, YELLOW);
	TargetInfo targets = GetTargets(e.id());
	flecs::entity_t target = 0;
	if (targets.leftTarget != 0 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		target = targets.leftTarget;
	}
	else if (targets.rightTarget != 0 && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
		target = targets.rightTarget;
	}
	if (target) {
		auto event = flecs::entity(world);
		event.add<Event>();
		event.set<Attack>({ target, e.id(),e.get<Card>().damage });
	}
};
auto registerTurnHandlerSystems = [&]() {
	TimerSystem_s.kind(flecs::OnUpdate);
	TimerSystem_s.action([&](flecs::rows rows, flecs::column<Timer> t) {
		if (EventsInProgresss) {
			return;
		}
		int minI = -1;
		float minT = -1;
		for (auto row : rows) {
			if (t[row].time <= 0) { //honestly negatives should not be possible but if they happen i will just treat them as zero
				minI = row;
				t[row].time = 0;
				minT = 0;
				break;
			}
			if (t[row].time < minT || minT < 0.0f) {
				minI = row;
				minT = t[row].time;
			}
		}
		assert(minT >= 0); //this should NEVER be negative
		for (auto row : rows) {
			t[row].time -= minT;
		}
		inputHandler(rows.entity(minI));
	});
	BlockInputSystem_s.kind(flecs::Manual);
	BlockInputSystem_s.action([&](flecs::rows row, flecs::column<Event> event) {
		EventsInProgresss = true;
	});
};
////////////////////////ENTITIES////////////////////////
auto registerTimerEntities = [&]() {
};