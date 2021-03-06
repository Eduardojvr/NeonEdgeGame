#include "LancelotGraphicsComponent.h"
#include "Lancelot.h"

LancelotGraphicsComponent::LancelotGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	AddSprite(baseName,"Idle",8,80);
	AddSprite(baseName,"Running",8,80);
	AddSprite(baseName,"Jumping",8,80,true);
	AddSprite(baseName,"Walled",1,0);
	AddSprite(baseName,"Crouching",4,80,true);
	AddSprite(baseName,"Blocking",6,80,true);
	AddSprite(baseName,"AttackingStraight",3,80,true);
	AddSprite(baseName,"AttackingUppercut",3,80,true);
	AddSprite(baseName,"AttackingChop",4,80,true);
	AddSprite(baseName,"AttackingSpear",3,80,true);
	AddSprite(baseName,"AttackingSword",3,80,true);
	AddSprite(baseName,"AttackingAxe",4,80,true);
	AddSprite(baseName,"Dying",5,50);
	sp = sprites["Idle"];
	surface = surfaces["Idle"];
}

LancelotGraphicsComponent::~LancelotGraphicsComponent()
{

}

void LancelotGraphicsComponent::Update(GameObject* obj, float dt)
{
	Lancelot* l = (Lancelot*) obj;

	mirror = (obj->facing == GameObject::LEFT);
	if(l->Attacking())
	{
		UpdateSprite(obj, "Attacking"+l->WhichCombo());
		if(obj->footing == GameObject::LEFT_WALLED || obj->footing == GameObject::RIGHT_WALLED)
			obj->footing = GameObject::AIRBORNE;
	}
	else if(l->Blocking())
	{
		UpdateSprite(obj, "Blocking");
		if(obj->footing == GameObject::LEFT_WALLED || obj->footing == GameObject::RIGHT_WALLED)
			obj->footing = GameObject::AIRBORNE;
	}
	else if(l->Crouching())
	{
		UpdateSprite(obj, "Crouching");
		if(obj->footing == GameObject::LEFT_WALLED || obj->footing == GameObject::RIGHT_WALLED)
			obj->footing = GameObject::AIRBORNE;
	}
	else if(obj->footing == GameObject::AIRBORNE)
	{
		UpdateSprite(obj, "Jumping");
	}
	else if(obj->footing == GameObject::LEFT_WALLED || obj->footing == GameObject::RIGHT_WALLED)
	{
		UpdateSprite(obj, "Walled");
		mirror = (obj->footing == GameObject::LEFT_WALLED);
	}
	else if(l->physicsComponent.velocity.x == 0)
	{
		UpdateSprite(obj, "Idle");
	}
	else
	{
		UpdateSprite(obj, "Running");
	}

	if (obj->dieTimer.IsRunning())
	{
		UpdateSprite(obj, "Dying");
	}

	sp->Mirror(mirror);
	sp->Update(dt);
}
