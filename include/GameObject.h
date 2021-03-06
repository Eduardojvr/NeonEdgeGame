#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>

#include "Rect.h"
#include "Vec2.h"
#include "TileMap.h"
#include "Timer.h"

class GameObject
{
public:
	enum Face : short int {UPPER, BOTTOM, LEFT, RIGHT, SPECIAL};
	enum Footing : short int {GROUNDED, LEFT_WALLED, RIGHT_WALLED, AIRBORNE};

	std::string name = "GameObject";
	Rect box = Rect();
	Face facing = RIGHT;
	Footing footing = GROUNDED; 
	Footing lastFooting = AIRBORNE;
	Timer dieTimer = Timer(1000);
	bool isDead=false;

	virtual ~GameObject() = 0;
	virtual bool Is(std::string type);
	virtual bool IsDead();
	virtual bool IsCharacter();
	virtual bool IsPlayer();
	virtual Vec2 GetPosition();
	virtual void SetPosition(Vec2 position);
	virtual void NotifyTileCollision(int tile, Face face);
	virtual void NotifyObjectCollision(GameObject* other);
	virtual void SolidCollision(GameObject* other);
	virtual bool GetColisionData(SDL_Surface** surface_, SDL_Rect &clipRect_, Vec2 &pos_, bool &mirror);
	virtual void Update(TileMap* map, float dt) = 0;
	virtual void Render() = 0;
	virtual void DieAnimation();
};

#endif /* GAMEOBJECT_H_ */
