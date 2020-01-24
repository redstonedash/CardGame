#pragma once

flecs::system<Card> DrawCardSystem_s(world, "DrawCardSystem");
auto registerDrawCardSystem = [&]() {
	DrawCardSystem_s.kind(flecs::OnStore);
	DrawCardSystem_s.action([&](flecs::rows rows, flecs::column<Card> card) {
		for (auto row : rows) {
			Vec2 data = FindMe(rows.entity(row).id());
			if (data.x == 0) {
				DrawModel(cardModel, { data.y * 0.005f - 0.01115f, 0, .0025f }, .00075f, RED);
			} else {
				DrawModel(cardModel, { data.y * -0.005f + 0.01115f, 0, -.0025f }, .00075f, BLUE);
			}
		}
	});
};

flecs::system<Card> DrawCardInfoSystem_s(world, "DrawCardInfoSystem");
auto registerDrawCardInfoSystem = [&]() {
	DrawCardInfoSystem_s.kind(flecs::Manual);
	DrawCardInfoSystem_s.action([&](flecs::rows rows, flecs::column<Card> card) {
		for (auto row : rows) {
			Vec2 data = FindMe(rows.entity(row).id());
			if (data.x == 0) {
				Vector2 pos = GetWorldToScreen({ data.y * 0.005f - 0.01115f, 0, .0025f }, cam);
				Card crd = rows.entity(row).get<Card>();
				DrawText("FUCK", pos.x, pos.y, 1, BLACK);
			} else {
				Vector2 pos = GetWorldToScreen({ data.y * -0.005f + 0.01115f, 0, -.0025f }, cam);
				DrawText("FUCK", pos.x, pos.y, 1, BLACK);
			}
		}
	});
	DrawCardInfoSystem_s.run();
};