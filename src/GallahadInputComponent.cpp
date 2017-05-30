#include "GallahadInputComponent.h"
#include "InputManager.h"
#include "Gallahad.h"

#define clamp(N,L,U) N=std::max(L,std::min(N,U))

GallahadInputComponent::GallahadInputComponent()
{

}

void GallahadInputComponent::Update(GameObject* obj, float dt)
{
	Gallahad* g = (Gallahad*) obj;
	InputManager &input = InputManager::GetInstance();
	// Move Left
	if(input.IsKeyDown(MOVE_LEFT_KEY, true))
	{
		g->physicsComponent.velocity.x -= 0.002*dt;
		g->facing = GameObject::LEFT;
	}
	// Move Right
	else if(input.IsKeyDown(MOVE_RIGHT_KEY, true))
	{
		g->physicsComponent.velocity.x += 0.002*dt;
		g->facing = GameObject::RIGHT;
	}
	// Stay Still
	else
	{
		g->physicsComponent.velocity.x = 0;
	}
	clamp(g->physicsComponent.velocity.x,-0.4f,0.4f);
	
	// Attack
	if(input.IsKeyDown(ATTACK_KEY,  true))
	{
		if(!g->Attacking())
		{
			g->Attack();
		}
	}
	
	//Hide
	if(input.IsKeyDown(SPECIAL_KEY, true))
	{
		if(g->GetEnergy() > 0 && !g->Hiding())
		{
			g->Hide();
		}
	}

	//Jump
	if(input.KeyPress(JUMP_KEY, true))
	{
		// Ground Jump
		if(g->footing == GameObject::GROUNDED)
		{
			g->physicsComponent.velocity.y = -0.6;
		}
		// Wall-Jump from a wall to the left
		else if(g->footing == GameObject::LEFT_WALLED && g->lastFooting != GameObject::LEFT_WALLED)
		{
			g->physicsComponent.velocity.y = -0.6;
			g->physicsComponent.velocity.x = 0.6;
			g->facing = GameObject::RIGHT;
			g->lastFooting = GameObject::LEFT_WALLED;
		}
		// Wall-Jump from a wall to the right
		else if(g->footing == GameObject::RIGHT_WALLED && g->lastFooting != GameObject::RIGHT_WALLED)
		{
			g->physicsComponent.velocity.y = -0.6;
			g->physicsComponent.velocity.x = -0.6;
			g->facing = GameObject::RIGHT;
			g->lastFooting = GameObject::RIGHT_WALLED;
		}
	}
}
