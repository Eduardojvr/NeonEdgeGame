#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.h"

class Camera {
private:
	GameObject* focus;

	static Camera* instance;

	Camera();
public:
	Vec2 pos;
	Vec2 speed;
    Vec2 maxPos;

	~Camera();
	void Follow(GameObject* newFocus);
	void Unfollow();
	void Update(float dt);
	void SetPos(Vec2 pos);
	GameObject* GetFocus();
	static Camera& GetInstance();
};

#endif /* CAMERA_H_ */
