#include <string>
Shader parallaxBG = LoadShader("resources/parallax.vert", "resources/parallaxBG.frag");
Shader parallaxFG = LoadShader("resources/parallax.vert", "resources/parallaxFG.frag");
int modelLocBG = GetShaderLocation(parallaxBG, "model");
int modelLocFG = GetShaderLocation(parallaxFG, "model");
int thicknessLocBG = GetShaderLocation(parallaxBG, "thickness");
int thicknessLocFG = GetShaderLocation(parallaxFG, "thickness");
int scaleLocBG = GetShaderLocation(parallaxBG, "scale");
int scaleLocFG = GetShaderLocation(parallaxFG, "scale");
auto LoadCardTextures = [&](const char* cardName, Model& model) {
	std::string filePath(cardName);
	std::string prefix("resources/");
	std::string temp = std::string();
	Texture cardTextures[5];
	cardTextures[0] = LoadTexture(temp.append(prefix).append(filePath).append("Depth.png").c_str());
	temp.clear();
	cardTextures[1] = LoadTexture(temp.append(prefix).append(filePath).append("Albedo.png").c_str());
	temp.clear();
	cardTextures[2] = LoadTexture(temp.append(prefix).append(filePath).append("Emmision.png").c_str());
	temp.clear();
	cardTextures[3] = LoadTexture(temp.append(prefix).append(filePath).append("Layer.png").c_str());
	SetShaderValueTexture(parallaxBG, GetShaderLocation(parallaxBG, "t3"), cardTextures[0]);
	SetShaderValueTexture(parallaxFG, GetShaderLocation(parallaxFG, "t3"), cardTextures[0]);
	temp.clear();
	cardTextures[4] = LoadTexture(temp.append(prefix).append(filePath).append("Normal.png").c_str());
	SetShaderValueTexture(parallaxBG, GetShaderLocation(parallaxBG, "t4"), cardTextures[4]);
	SetShaderValueTexture(parallaxFG, GetShaderLocation(parallaxFG, "t4"), cardTextures[4]);
	model.materials[0].shader = parallaxBG;
	model.materials[2].shader = parallaxFG;
	for (int i = 0; i < 5; i++) {
		model.materials[0].maps[i].texture = cardTextures[i];
		model.materials[2].maps[i].texture = cardTextures[i];
	}
	//TODO add thickness	
};
//////////////////////////VARIABLES & STRUCTS//////////////////////////
struct Card {
	float thickness; //the scale that the heighmap should be scaled by
};
//shader

Model cardTemplate = LoadModel("resources/Card.glb");

Texture hyenaTexture[5];

//////////////////////////COMPONENTS//////////////////////////
flecs::component<Card> Card_c(world, "Card");
//////////////////////////SYSTEMS//////////////////////////
auto registerCardSystems = [&] {
	flecs::system<Card>(world, "DrawParallaxObjects").kind(flecs::	PostUpdate).action([&](flecs::rows rows, flecs::column<Card> card) {
		for (auto row : rows) {
			Ray r = GetMouseRay(GetMousePosition(), cam);
			Vector3 v = { r.position.x,0,r.position.z };
			float scale = 3;
			SetShaderValue(parallaxBG, modelLocBG, &v, UNIFORM_VEC3);
			SetShaderValue(parallaxBG, scaleLocBG, &scale, UNIFORM_FLOAT);
			SetShaderValue(parallaxBG, thicknessLocBG, &(card[row].thickness), UNIFORM_FLOAT);
			SetShaderValue(parallaxFG, modelLocFG, &v, UNIFORM_VEC3);
			SetShaderValue(parallaxFG, scaleLocFG, &scale, UNIFORM_FLOAT);
			SetShaderValue(parallaxFG, thicknessLocFG, &(card[row].thickness), UNIFORM_FLOAT);
			DrawModel(cardTemplate, { r.position.x,0,r.position.z }, 2, WHITE);
		}
	});
};
//////////////////////////ENTITIES//////////////////////////
auto registerCardEntities = [&] {
	auto testCard_e = flecs::entity(world);
	testCard_e.add<Card>();
	testCard_e.set<Model>(cardTemplate);
	Model* m = testCard_e.get_ptr<Model>();
	*m = cardTemplate;
	LoadCardTextures("hyena", *m);
	Card * c = testCard_e.get_ptr<Card>();
	c->thickness = 0.05f;

	//c->textures[0].texture =
};