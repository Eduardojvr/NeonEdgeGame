#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "GameObject.h"
#include "Vec2.h"
#include "Timer.h"
#include "TileMap.h"
#include "PhysicsComponent.h"
#include "ProjectileGraphicsComponent.h"


class Projectile : public GameObject
{
private:
	Timer lifetime = Timer();
	int power = 0;
	GameObject* owner = nullptr;
	bool pierce;

public:
	Projectile(GameObject* owner, Vec2 speed, int lifetime, int power, bool pierce = false);
	~Projectile();
	bool IsDead();
	int Power();
	GameObject* GetOwner();
	bool GetColisionData(SDL_Surface** surface_,SDL_Rect &clipRect_,Vec2 &pos_, bool &mirror);
	void NotifyTileCollision(int tile, Face face);
	void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void Update(TileMap* world, float dt);
	void Render();

	PhysicsComponent physicsComponent;
	ProjectileGraphicsComponent* graphicsComponent;
};

#endif /* PROJECTILE_H_ */
