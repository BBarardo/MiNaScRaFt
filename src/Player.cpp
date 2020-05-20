#include "Player.h"

#include <chrono>
#include <iostream>
#include <math.h>



Player::Player(Camera& camera, glm::vec3 pos) :camera(&camera), pos(pos)
{
}

Player::~Player()
{

}

void Player::move(Camera_Movement direction, float deltaTime)
{
	glm::vec3 front = camera->Front;
	glm::vec3 right = camera->Right;
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
	{
		this->pos.x += front.x * velocity;
		this->pos.z += front.z * velocity;
	}
	if (direction == BACKWARD)
	{
		this->pos.x -= front.x * velocity;
		this->pos.z -= front.z * velocity;
	}
	if (direction == LEFT)
	{
		this->pos.x -= right.x * velocity;
		this->pos.z -= right.z * velocity;
	}
	if (direction == RIGHT)
	{
		this->pos.z += right.z * velocity;
		this->pos.x += right.x * velocity;
	}
	if (direction == UP)
		jump();
	
	std::cout << "player: " << pos.x << ", " << pos.y << ", " << pos.z << "\n";
	std::cout << "camera::front: " << front.x << ", " << front.y << ", " << front.z << "\n";

}

void Player::jump()
{
	if(!jumping)
	{
		velocityY = 5.5;
		pos.y += 1;
		jumping = true;
	}
}

void Player::update(float deltaTime)
{

	//gravidade
	if(pos.y > 0 && jumping)
	{
		velocityY -= 0.5;
		pos.y += velocityY * deltaTime;
	}else
	{
		jumping = false;
	}

	//y-2 para a camera ficar a altura da "cabeça"
	camera->Position.x = this->pos.x;
	camera->Position.y = this->pos.y + 2;
	camera->Position.z = this->pos.z;
	std::cout << "velocityY: " << velocityY << "\n";
}