#include "camera.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include <glm/glm.hpp>
#include <glm/geometric.hpp>

Camera::Camera()
{

}

void Camera::zoom(float amount)
{
    rho += amount;
}

void Camera::rotateDirection(float amount, bool axis)
{
    if (!axis) // theta
	theta += amount;
    else
	phi += amount;
}

glm::mat4 Camera::getViewProjectionMatrix()
{
    // First, find the camera position
    float cam_x, cam_y, cam_z;

    cam_x = rho * cos(phi) * sin(theta);
    cam_y = rho * sin(phi) * sin(theta);
    cam_z = rho * sin(theta);

    glm::mat4 ret;

    glm::vec3 cameraPos = glm::vec3(cam_x, cam_y, cam_z);
    glm::vec3 cameraDirection = glm::normalize(cameraPos);

    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos - cameraDirection, cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(50.0f), (float)800 / (float)600, 0.1f, 1000.0f);

    ret = projection * view;

    return ret;
}

