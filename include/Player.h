#ifndef PLAYER_H
#define PLAYER_H

#include <camera.h>

class Player
{
	glm::vec3 pos;
	Camera* camera;
	const float MovementSpeed = 7.5;
	float gravity = 5.5;
	float accelerationY;
	float newForce = gravity + accelerationY;
	float velocityY = 0;

	bool jumping;

	void jump();
	
public:
	Player();
	Player(Camera& camera, glm::vec3 pos = glm::vec3(0,0,0));
	~Player();
	void move(Camera_Movement direction, float deltaTime);
	void update(float deltaTime);
};

#endif

