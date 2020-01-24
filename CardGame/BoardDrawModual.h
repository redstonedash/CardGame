#pragma once
////////////////////////STRUCTS AND STUFF////////////////////////

////////////////////////COMPONENTS////////////////////////
flecs::component<CardVisuals> CardVisuals_c(world, "CardVisuals");
////////////////////////SYSTEMS////////////////////////
flecs::system<Card, CardVisuals> DrawCardSystem_s(world, "DrawCardSystem");
flecs::system<Card> DrawCardInfoSystem_s(world, "DrawCardInfoSystem");

auto registerDrawCardSystem = [&]() {
	DrawCardSystem_s.kind(flecs::OnStore);
	DrawCardSystem_s.action([&](flecs::rows rows, flecs::column<Card> card, flecs::column<CardVisuals> cv) {
		//CardVisuals cv is SHARED, this means there is only one per run of the system, this system will be ran once for each type of cv exist
		//if (!cv.is_shared()) return; //you should be able to do this in the system signature but i fogot how 12:15
		//nvm game jam moment 1:09
		for (auto row : rows) {
			Vec2 data = FindMe(rows.entity(row).id());
			Vector3 v = {0,0,0};
			float spacing = 0.5;
			if (data.x == 0) {
				v = { data.y * (spacing*5) - (spacing) - 5.0f, 0, 1.75f }; //sorry this isn't clean 1:15
			}
			else {
				v = { data.y * (spacing*5) + (spacing) - 5.0f, 0, -1.75f };
			}
			float scale = 3;
			SetShaderValue(parallaxBG, modelLocBG, &v, UNIFORM_VEC3);
			SetShaderValue(parallaxBG, scaleLocBG, &scale, UNIFORM_FLOAT);
			SetShaderValue(parallaxBG, thicknessLocBG, &(cv[row].thickness), UNIFORM_FLOAT);
			SetShaderValue(parallaxFG, modelLocFG, &v, UNIFORM_VEC3);
			SetShaderValue(parallaxFG, scaleLocFG, &scale, UNIFORM_FLOAT);
			SetShaderValue(parallaxFG, thicknessLocFG, &(cv[row].thickness), UNIFORM_FLOAT);
			cardModel.materials[0] = cv[row].background;
			cardModel.materials[2] = cv[row].foreground;
			DrawModel(cardModel, v, 1, WHITE);
		}
	});
	DrawCardInfoSystem_s.kind(flecs::Manual);
	DrawCardInfoSystem_s.action([&](flecs::rows rows, flecs::column<Card> card) {
		for (auto row : rows) {
			Vec2 data = FindMe(rows.entity(row).id());
			float spacing = 0.5;
			char healthField[64];
			Health* hp = rows.entity(row).get_ptr<Health>();
			if (hp) {
				sprintf_s(healthField, 64, "%d", hp->health);
			}
			char attackField[64];
			Vector3 pos;
			sprintf_s(attackField, 64, "%d", card[row].damage);
			if (data.x == 0) {
				pos = { data.y * (spacing * 5) - (spacing) - 5.0f, 0, 1.75f };
			}
			else {
				pos = { data.y * (spacing * 5) + (spacing) - 5.0f, 0, -1.75f };
			}
			Vector2 offset = GetWorldToScreen(Vector3Subtract(pos, { 0.5f, 0, -1.75f }), cam);
			DrawText(attackField, offset.x, offset.y, 1, RED);
			offset = GetWorldToScreen(Vector3Subtract(pos, { -0.5f, 0, -1.75f }), cam);
			DrawText(healthField, offset.x, offset.y, 1, GREEN);
			offset = GetWorldToScreen(Vector3Subtract(pos, { -0.5f, 0, -1.75f }), cam);
			Vector2 offset2 = GetWorldToScreen(Vector3Subtract(pos, { 0.5f, 0, -2.0f }), cam); //TODO DRAW TIMER
			DrawRectangle(offset.x, offset.y,offset2.x- offset.x, offset2.y- offset.y, WHITE);
		}
	});
};
////////////////////////ENTITIES////////////////////////