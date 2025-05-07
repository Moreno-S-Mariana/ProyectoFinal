#pragma once
#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <glfw3.h>

class Camera
{
public:
    Camera();
    Camera(glm::vec3 startPosition,
        glm::vec3 startUp,
        GLfloat   startYaw,
        GLfloat   startPitch,
        GLfloat   startMoveSpeed,
        GLfloat   startTurnSpeed);
    ~Camera();

    void keyControl(bool* keys, GLfloat deltaTime);
    void mouseControl(GLfloat xChange, GLfloat yChange);

    glm::mat4 calculateViewMatrix();
    glm::vec3 getCameraPosition();
    glm::vec3 getCameraDirection();

    void setPosition(const glm::vec3& newPos);
    void setOrientation(GLfloat newYaw, GLfloat newPitch);
    void syncWithTarget();
    void toggleTopView();

    void setFollowTarget(glm::vec3* targetPos, GLfloat* targetYaw, glm::vec3 eyeOffset = glm::vec3(0.0f, 1.8f, 0.0f));
    void activateAutoFollow();
    bool isFollowModeActive() const;
    void setTargetPointer(glm::vec3* ptr);

    void terceraPersona(glm::vec3* targetPos, GLfloat* targetYaw); // nuevo método expuesto

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    GLfloat   yaw;
    GLfloat   pitch;

    GLfloat   moveSpeed;
    GLfloat   turnSpeed;

    glm::vec3* targetPosPtr = nullptr;
    GLfloat* targetYawPtr = nullptr;
    glm::vec3  eyeOffset = glm::vec3(0.0f, 8.0f, 15.0f);
    GLfloat yawOffsetFromMouse = 0.0f;

    bool autoFollowEnabled = false;
    bool followMode = false;

    bool topView = false;
    glm::vec3 savedPosition;
    glm::vec3 savedFront;
    glm::vec3 savedUp;
    glm::vec3 savedTopPosition;

    void update();
};
