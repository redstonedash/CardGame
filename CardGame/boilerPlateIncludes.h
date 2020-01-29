#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include "raylib.h"
#include "rlgl.h"
#include "flecs.h"
#include "flecs/flecs.hpp"
#include "raymath.h"
#include <inttypes.h>

//Models
Model cardModel;

//Images
Texture vignette;

//Sounds
Music music;

template<typename T> T* addrOf(T&& v) { return &v; }
#undef ecs_set

#define ecs_set(world, entity, component, ...)\
    _ecs_set_ptr(world, entity, ecs_entity(component), sizeof(component), addrOf(component __VA_ARGS__))

#define ecs_set_ref(world, entity, component, ...)\
    _ecs_set_ptr(world, entity, ecs_entity(component), sizeof(component), &__VA_ARGS__)

_declspec(selectany) flecs::world world = flecs::world();

_declspec(selectany) struct Card { //all values are base values
	int damage;
	int HP;
	float cost;
	float BAT; //base attack time
	float summonSickness;
};

_declspec(selectany) struct TargetInfo {
	flecs::entity_t leftTarget;
	flecs::entity_t rightTarget;
};

struct Timer {
	float time;
};

Vector2 GetWorldToTexture(Vector3 position, Camera camera, int screenWidth, int screenHeight)
{
	// Calculate projection matrix (from perspective instead of frustum
	Matrix matProj = MatrixIdentity();

	if (camera.type == CAMERA_PERSPECTIVE)
	{
		// Calculate projection matrix from perspective
		matProj = MatrixPerspective(camera.fovy * DEG2RAD, ((double)screenWidth / (double)screenHeight), 0.01, 1000.0);
	}
	else if (camera.type == CAMERA_ORTHOGRAPHIC)
	{
		float aspect = (float)screenWidth / (float)screenHeight;
		double top = camera.fovy / 2.0;
		double right = top * aspect;

		// Calculate projection matrix from orthographic
		matProj = MatrixOrtho(-right, right, -top, top, 0.01, 1000.0);
	}

	// Calculate view matrix from camera look at (and transpose it)
	Matrix matView = MatrixLookAt(camera.position, camera.target, camera.up);

	// Convert world position vector to quaternion
	Quaternion worldPos = { position.x, position.y, position.z, 1.0f };

	// Transform world position to view
	worldPos = QuaternionTransform(worldPos, matView);

	// Transform result to projection (clip space position)
	worldPos = QuaternionTransform(worldPos, matProj);

	// Calculate normalized device coordinates (inverted y)
	Vector3 ndcPos = { worldPos.x / worldPos.w, -worldPos.y / worldPos.w, worldPos.z / worldPos.w };

	// Calculate 2d screen position vector
	Vector2 screenPosition = { (ndcPos.x + 1.0f) / 2.0f * (float)screenWidth, (ndcPos.y + 1.0f) / 2.0f * (float)screenHeight };

	return screenPosition;
}

struct Health {
	int health;
};

struct Attack {
	flecs::entity_t target;
	flecs::entity_t attacker;
	int damage;

};

struct Vec2 {
	int x;
	int y;
};

flecs::entity HandP1[10]; // in the future theses should not store cards directly
flecs::entity HandP2[10];
flecs::entity_t Board[2][5];

auto FindMe = [&](flecs::entity_t id) -> Vec2 {
	for (int i = 0; i < 5; i++) {
		if (Board[0][i] == id) {
			return { 0,i };
		}
		if (Board[1][i] == id) {
			return { 1,i };
		}
	}
	return { -1, -1 }; //TODO add a check at every reference to this function
};

auto GetTargets = [&](flecs::entity_t id) -> TargetInfo { // in the future the board should also contain entity references to left and right
	Vec2 pos = FindMe(id);
	if (pos.y == 0) {
		return { 0, Board[!pos.x][4 - pos.y] };
	} else {
		assert(flecs::entity(world, Board[!pos.x][4 - pos.y]).get_ptr<Health>());
		assert(flecs::entity(world, Board[!pos.x][5 - pos.y]).get_ptr<Health>());
		return { Board[!pos.x][5 - pos.y], Board[!pos.x][4 - pos.y] };
	}
};

bool addCardToBoard(Vec2 v, flecs::entity_t card) {
	if (Board[v.x][v.y] != 0) {
		return false;
	}
	Board[v.x][v.y] = card;
	return true;
}
struct CardVisuals {
	float thickness; //the scale that the heighmap should be scaled by
	Material foreground;
	Material background;
};

struct Event {
	float timeElapsed;
	int framesElapsed;
	void (*eventFunction)(float, int);
};

Shader parallaxBG	;
Shader parallaxFG	;
int modelLocBG		;
int modelLocFG		;
int thicknessLocBG	;
int thicknessLocFG  ;
int scaleLocBG		;
int scaleLocFG		;

void initParalax() {
	parallaxBG = LoadShader("resources/parallax.vert", "resources/parallaxBG.frag");
	parallaxFG = LoadShader("resources/parallax.vert", "resources/parallaxFG.frag");
	modelLocBG = GetShaderLocation(parallaxBG, "model");
	modelLocFG = GetShaderLocation(parallaxFG, "model");
	thicknessLocBG = GetShaderLocation(parallaxBG, "thickness");
	thicknessLocFG = GetShaderLocation(parallaxFG, "thickness");
	scaleLocBG = GetShaderLocation(parallaxBG, "scale");
	scaleLocFG = GetShaderLocation(parallaxFG, "scale");
}

CardVisuals LoadCardVisuals(const char* cardName) {
	CardVisuals card = {};
	std::string filePath(cardName);
	std::string prefix("resources/");
	std::string temp = std::string();
	Texture cardTextures[3];
	cardTextures[0] = LoadTexture(temp.append(prefix).append(filePath).append("Depth.png").c_str());
	temp.clear();
	cardTextures[1] = LoadTexture(temp.append(prefix).append(filePath).append("Albedo.png").c_str());
	temp.clear();
	cardTextures[2] = LoadTexture(temp.append(prefix).append(filePath).append("Layer.png").c_str());
	temp.clear();
	card.background = LoadMaterialDefault();
	card.foreground = LoadMaterialDefault();
	card.background.shader = parallaxBG;
	card.foreground.shader = parallaxFG;
	
	for (int i = 0; i < 3; i++) {
		card.foreground.maps[i].texture = cardTextures[i];
		card.background.maps[i].texture = cardTextures[i];
	}
	return card;
	//TODO add thickness	
};