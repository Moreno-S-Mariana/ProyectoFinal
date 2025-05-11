#pragma once

#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <glfw3.h>

// Enum para el modo de cámara (debe coincidir con el que ya usas en main)
enum CameraMode {
	FIRST_PERSON,
	THIRD_PERSON,
	TOP_VIEW,
	ATTRACTIONS
};

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void keyControl(bool* keys, GLfloat deltaTime, CameraMode camMode);
	void mouseControl(GLfloat xChange, GLfloat yChange);

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	glm::mat4 calculateViewMatrix();

	//  Getters añadidos
	float getYaw() const { return yaw; }
	float getPitch() const { return pitch; }

	void setPosition(const glm::vec3& pos) { position = pos; }
	void setYaw(float y) { yaw = y; update(); }
	void setPitch(float p) { pitch = p; update(); }
	void lookAt(const glm::vec3& target) {
		front = glm::normalize(target - position);
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}
	void setDirection(glm::vec3 newFront) {
		front = glm::normalize(newFront);
		update();
	}

	// Métodos añadidos para tercera persona
	void setCameraPosition(const glm::vec3& pos) { position = pos; }
	void setCameraFront(const glm::vec3& frontVec) { front = glm::normalize(frontVec); }

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	void update();
};
