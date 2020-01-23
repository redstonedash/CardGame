#pragma once

flecs::system<Card> DrawCardSystem_s(world, "DrawCardSystem");
auto registerDrawCardSystem = [&]() {
	DrawCardSystem_s.kind(flecs::Manual);
	DrawCardSystem_s.action([&](flecs::rows rows, flecs::column<Card> card) {
		for (auto row : rows) {
			rows.entity(row).id();
		}
	});
};