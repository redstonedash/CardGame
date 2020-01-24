////////////////////////STRUCTS AND STUFF////////////////////////

////////////////////////COMPONENTS////////////////////////

////////////////////////SYSTEMS////////////////////////
flecs::system<Card> InitCard_s(world, "InitCard");
auto registerInitCardSystems = [&](){
	InitCard_s.kind(flecs::OnSet);
	InitCard_s.action([&](flecs::rows rows, flecs::column<Card> card) {
		for (auto row : rows) {
			rows.entity(row).set<Health>({ card[row].HP });
			rows.entity(row).set<Timer>({ card[row].summonSickness });
			rows.entity(row).add<CardVisuals>();
		}
	});	
};
////////////////////////ENTITIES////////////////////////