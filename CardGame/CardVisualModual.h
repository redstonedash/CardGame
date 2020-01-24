
//shader

Model cardTemplate = LoadModel("resources/Card.glb");

Texture hyenaTexture[5];

//////////////////////////COMPONENTS//////////////////////////
flecs::component<Card> Card_c(world, "Card");
//////////////////////////SYSTEMS//////////////////////////
auto registerCardSystems = [&] {
	flecs::system<Card>(world, "DrawParallaxObjects").kind(flecs::	PostUpdate).action([&](flecs::rows rows, flecs::column<Card> card) {
		for (auto row : rows) {
			
			
			DrawModel(cardTemplate, { r.position.x,0,r.position.z }, 2, WHITE);
		}
	});
};
//////////////////////////ENTITIES//////////////////////////