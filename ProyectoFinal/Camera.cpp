#include "Camera.h"

Camera::Camera()
    : topView(false),
    savedTopPosition(glm::vec3(0.0f, 150.0f, 0.0f)),
    followMode(false),
    autoFollowEnabled(false),
    targetPosPtr(nullptr),
    targetYawPtr(nullptr),
    eyeOffset(0.0f, 25.0f, 15.0f),
    yawOffsetFromMouse(0.0f) {
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
    : topView(false),
    savedTopPosition(glm::vec3(0.0f, 150.0f, 0.0f)),
    followMode(false),
    autoFollowEnabled(false),
    targetPosPtr(nullptr),
    targetYawPtr(nullptr),
    eyeOffset(0.0f, 8.0f, 15.0f),
    yawOffsetFromMouse(0.0f),
    position(startPosition),
    worldUp(startUp),
    yaw(startYaw),
    pitch(startPitch),
    front(glm::vec3(0.0f, 0.0f, -1.0f)),
    moveSpeed(startMoveSpeed),
    turnSpeed(startTurnSpeed) {
    update();
}

void Camera::terceraPersona(glm::vec3* targetPos, GLfloat* targetYaw) {
    targetPosPtr = targetPos;
    targetYawPtr = targetYaw;
    followMode = true;
    autoFollowEnabled = true;
}

void Camera::syncWithTarget() {
    if (!followMode || !targetPosPtr || !targetYawPtr) return;

    const float heightOffset = 25.0f;
    const float distBehind = 20.0f;

    float yawRad = *targetYawPtr;

    glm::vec3 forward = glm::vec3(sin(yawRad), 0.0f, cos(yawRad));
    glm::vec3 camOffset = -forward * distBehind;
    camOffset.y = heightOffset;

    position = *targetPosPtr + camOffset;

    yaw = glm::degrees(yawRad);
    pitch = -10.0f;

    update();
}

void Camera::setTargetPointer(glm::vec3* ptr) {
    targetPosPtr = ptr;
}

void Camera::setFollowTarget(glm::vec3* targetPos, GLfloat* targetYaw, glm::vec3 offset) {
    targetPosPtr = targetPos;
    targetYawPtr = targetYaw;
    eyeOffset = offset;
    followMode = true;
    autoFollowEnabled = true;
}

void Camera::activateAutoFollow() {
    autoFollowEnabled = true;
    followMode = true;
}

void Camera::keyControl(bool* keys, GLfloat deltaTime) {
    static bool prevUp = false;
    static bool prevDown = false;

    GLfloat velocity = moveSpeed * deltaTime;
    GLfloat angVel = turnSpeed * deltaTime;

    if (followMode && targetPosPtr && targetYawPtr) {
        glm::vec3 forwardDir = glm::normalize(glm::vec3(sin(*targetYawPtr), 0.0f, cos(*targetYawPtr)));

        if (keys[GLFW_KEY_UP] && !prevUp) {
            *targetPosPtr += forwardDir * velocity;
        }
        prevUp = keys[GLFW_KEY_UP];

        if (keys[GLFW_KEY_DOWN] && !prevDown) {
            *targetPosPtr -= forwardDir * velocity;
        }
        prevDown = keys[GLFW_KEY_DOWN];

        if (keys[GLFW_KEY_LEFT]) {
            *targetYawPtr -= angVel;
        }
        if (keys[GLFW_KEY_RIGHT]) {
            *targetYawPtr += angVel;
        }

        syncWithTarget();
    }

    update();
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw += xChange;
    pitch += yChange;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    update();
}

glm::mat4 Camera::calculateViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition() {
    return position;
}

glm::vec3 Camera::getCameraDirection() {
    return glm::normalize(front);
}

void Camera::update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::setPosition(const glm::vec3& newPos) {
    position = newPos;
}

void Camera::setOrientation(GLfloat newYaw, GLfloat newPitch) {
    yaw = newYaw;
    pitch = newPitch;
    update();
}

void Camera::toggleTopView() {
    if (!topView) {
        savedPosition = position;
        savedFront = front;
        savedUp = up;
        position = savedTopPosition;
        front = glm::vec3(0.0f, -1.0f, 0.0f);
        up = glm::vec3(0.0f, 0.0f, -1.0f);
    }
    else {
        savedTopPosition = position;
        position = savedPosition;
        front = savedFront;
        up = savedUp;
    }
    topView = !topView;
    update();
}

bool Camera::isFollowModeActive() const {
    return followMode;
}

Camera::~Camera() {}