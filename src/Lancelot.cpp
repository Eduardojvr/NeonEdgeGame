#include "Lancelot.h"
#include "Camera.h"
#include "Attack.h"


Lancelot::Lancelot(int x, int y):
	inputComponent(),
	physicsComponent(),
	graphicsComponent("Lancelot"),
	saveComponent(SaveComponent::GetInstance())
{
	name = "Lancelot";
	Vec2 size = graphicsComponent.GetSize();
	box = Rect(x, y, size.x, size.y);
	facing = RIGHT;
}

Lancelot::~Lancelot()
{

}

bool Lancelot::IsDead()
{
	return (hitpoints < 1);
}

int Lancelot::GetHealth()
{
	return hitpoints;
}

void Lancelot::Damage(int damage)
{
	if(!invincibilityTimer.IsRunning()) 
	{
		hitpoints -= (damage);
		invincibilityTimer.Start();
	}
}

void Lancelot::Attack()
{
	attacking.Start();
}

bool Lancelot::Attacking()
{
	return attacking.IsRunning();
}

void Lancelot::NotifyTileCollision(int tile, Face face)
{
	if(tile > 11)
	{
		Damage(1);
	}
}

void Lancelot::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Attack"))
	{
		//Attack* a = (Attack*) other;
		//if(a->owner->Is("Lancelot"))
			Damage(1);
	}
}

void Lancelot::UpdateTimers(float dt)
{
	invincibilityTimer.Update(dt);
	attacking.Update(dt);
}

void Lancelot::Update(float dt)
{
	UpdateTimers(dt);
	inputComponent.Update(this,dt);
	physicsComponent.Update(this,dt);
	graphicsComponent.Update(this,dt);
	saveComponent.Update(this,dt);
}

void Lancelot::Render()
{
	graphicsComponent.Render(GetPosition()-Camera::GetInstance().pos);
}
