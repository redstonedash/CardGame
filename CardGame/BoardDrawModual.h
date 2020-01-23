#pragma once

flecs::system<Card> DrawCardSystem_s(world, "DrawCardSystem");
auto registerDrawCardSystem = [&]() {
	DrawCardSystem_s.kind(flecs::Manual);
	DrawCardSystem_s.action([&](flecs::rows rows, flecs::column<Card> card) {
		for (auto row : rows) {
			Vec2 data = FindMe(rows.entity(row).id());
			if (data.x == 0) {
				DrawPlane({ (float)(10 * data.y), -100, 10 }, { .25f, .75f }, RED);
			}
			else {
				DrawPlane({ (float)(10 * data.y), -100, -10 }, { .25f, .75f }, BLUE);
			}
		}
	});
};