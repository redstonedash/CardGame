////////////////////////STRUCTS AND VARIABLES/////////////
////////////////////////COMPONENTS////////////////////////
flecs::component<Card> Card_c(world, "Card");
////////////////////////SYSTEMS//////////////////////////
flecs::system<Card> CardSystem_s(world, "CardSystem");
auto registerCardSystems = [&]() {
	CardSystem_s.kind(flecs::Manual);
	CardSystem_s.action([&](flecs::rows rows, flecs::column<Card> card) {
		for (auto row : rows) {

		}
	});
};
////////////////////////ENTITIES////////////////////////