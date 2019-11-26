#include "Camera.h"

Camera::Camera(glm::vec3 up) :  worldUp(up)
{
}

void Camera::set_position(glm::vec3 pos)
{
    position = pos;
    front.x = .0f;   //cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = .0f;   //sin(glm::radians(pitch));
    front.z = -1.0f; //sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::calculateViewMatrix()
{
    return glm::lookAt(position,
                       position + front,
                       up);
}
