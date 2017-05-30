#include "LancelotInputComponent.h"
#include "InputManager.h"
#include "Lancelot.h"

#define clamp(N,L,U) N=std::max(L,std::min(N,U))

LancelotInputComponent::LancelotInputComponent()
{

}

void LancelotInputComponent::Update(GameObject* obj, float dt)
{
	Lancelot* l = (Lancelot*) obj;
	InputManager &input = InputManager::GetInstance();
	// Move Left
	if(input.IsKeyDown(MOVE_LEFT_KEY, true))
	{
		l->physicsComponent.velocity.x -= 0.002*dt;
		l->facing = GameObject::LEFT;
	}
	// Move Right
	else if(input.IsKeyDown(MOVE_RIGHT_KEY, true))
	{
		l->physicsComponent.velocity.x += 0.002*dt;
		l->facing = GameObject::RIGHT;
	}
	// Stay Still
	else
	{
		l->physicsComponent.velocity.x = 0;
	}
	if(l->Crouching())
		clamp(l->physicsComponent.velocity.x,-0.2f,0.2f);
	else
		clamp(l->physicsComponent.velocity.x,-0.4f,0.4f);

	//Crouch
	if(input.IsKeyDown(CROUCH_KEY,  true))
	{
		l->Crouch();
	}
	else
	{
		l->Stand();
	}

	// Attack
	if(input.IsKeyDown(ATTACK_KEY,  true))
	{
		if(!l->Attacking())
		{
			l->Attack();
		}
	}
	
	//Block
	if(input.IsKeyDown(SPECIAL_KEY, true))
	{
		if(l->GetEnergy() > 0 && !l->Blocking())
		{
			l->Block();
		}
	}

	// Jump
	if(input.KeyPress(JUMP_KEY, true))
	{
		// Ground Jump
		if(l->footing == GameObject::GROUNDED)
		{
			l->physicsComponent.velocity.y = -0.6;
		}
		// Wall-Jump from a wall to the left
		else if(l->footing == GameObject::LEFT_WALLED && l->lastFooting != GameObject::LEFT_WALLED)
		{
			l->physicsComponent.velocity.y = -0.6;
			l->physicsComponent.velocity.x = 0.6;
			l->facing = GameObject::RIGHT;
			l->lastFooting = GameObject::LEFT_WALLED;
		}
		// Wall-Jump from a wall to the right
		else if(l->footing == GameObject::RIGHT_WALLED && l->lastFooting != GameObject::RIGHT_WALLED)
		{
			l->physicsComponent.velocity.y = -0.6;
			l->physicsComponent.velocity.x = -0.6;
			l->facing = GameObject::RIGHT;
			l->lastFooting = GameObject::RIGHT_WALLED;
		}
	}
	
	if(input.MousePress(LEFT_MOUSE_BUTTON))
	{
		l->saveComponent.Save(true);
		l->saveComponent.Update(l, "savefile.txt");
		/*int a = 0;
		for (auto i : StageState::objectArray)
		{
			std::string b = a;
			i->SaveComponent::Save(true);
			i->SaveComponent::Update(i, "saveenemy" + b + ".txt");
			a++;
		}*/
	}

	if(input.MousePress(RIGHT_MOUSE_BUTTON))
	{
		l->saveComponent.Save(false);
		l->saveComponent.Update(l, "savefile.txt");
		/*int a = 0;
		for (auto i : StageState::objectArray)
		{
			std::string b = a;
			i->SaveComponent::Save(false);
			i->SaveComponent::Update(i, "saveenemy" + b + ".txt");
			a++;
		}*/
	}	
}
