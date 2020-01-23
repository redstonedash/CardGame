#pragma once

flecs::system<Card> DrawCardSystem_s(world, "DrawCardSystem");
auto registerDrawCardSystem = [&]() {
	DrawCardSystem_s.kind(flecs::OnStore);
	DrawCardSystem_s.action([&](flecs::rows rows, flecs::column<Card> card) {
		for (auto row : rows) {
			Vec2 data = FindMe(rows.entity(row).id());
			if (data.x == 0) {
				DrawModel(cardModel, { data.y * 0.001f, 0, .005f }, .001f, RED);
			} else {
				DrawModel(cardModel, { data.y * 0.001f, 0, -.005f }, .001f, BLUE);
			}
		}
	});
};