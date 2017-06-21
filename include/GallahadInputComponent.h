#ifndef GALLAHADINPUTCOMPONENT_H
#define GALLAHADINPUTCOMPONENT_H

#include "InputComponent.h"

class GallahadInputComponent: public InputComponent
{
public:
	GallahadInputComponent();
	void Update(Player* obj_, float dt_);
	void Hide();
};

#endif // GALLAHADINPUTCOMPONENT_H
