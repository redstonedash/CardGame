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
	cardTextures[2] = LoadTexture(temp.append(prefix).append(filePath).append("Layer.png").c_str());
	temp.clear();
	model.materials[0].shader = parallaxBG;
	model.materials[2].shader = parallaxFG;
	for (int i = 0; i < 5; i++) {
		model.materials[0].maps[i].texture = cardTextures[i];
		model.materials[2].maps[i].texture = cardTextures[i];
	}
	//TODO add thickness	
};
//////////////////////////VARIABLES & STRUCTS//////////////////////////
struct CardVisuals {
	float thickness; //the scale that the heighmap should be scaled by
	Material foreground;
	Material background;
};
//shader

Model cardTemplate = LoadModel("resources/Card.glb");

Texture hyenaTexture[5];

//////////////////////////COMPONENTS//////////////////////////
flecs::component<CardVisuals> CardModel_c(world, "Card");
//////////////////////////SYSTEMS//////////////////////////
auto registerCardSystems = [&] {
	flecs::system<CardVisuals>(world, "DrawParallaxObjects").kind(flecs::PostUpdate).action([&](flecs::rows rows, flecs::column<Card> card) {
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
			DrawModel(cardModel, { r.position.x,0,r.position.z }, 2, WHITE);
		}
	});
};
//////////////////////////ENTITIES//////////////////////////