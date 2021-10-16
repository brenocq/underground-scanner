#include "camera.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include <glm/glm.hpp>
#include <glm/geometric.hpp>

#include <stdio.h>
#include <iostream>

Camera::Camera():
    rho(60), phi(glm::radians(45.0f)), theta(glm::radians(270.0f))
{

}

void Camera::zoom(float amount)
{
    rho -= amount;
}

void Camera::rotateDirection(float amount, bool axis)
{
    if(!axis)
    {
	    theta += amount;
        while(theta <= 0) theta += 2*M_PI;
        while(theta >= 2*M_PI) theta -= 2*M_PI;
    }
    else
    {
        if(phi+amount >= 0 && phi+amount <= M_PI)
            phi += amount;
    }
}

glm::mat4 Camera::getViewProjectionMatrix()
{
    // First, find the camera position
    float cam_x, cam_y, cam_z;
    cam_x = rho * cos(theta) * sin(phi);
    cam_y = rho * sin(theta) * sin(phi);
    cam_z = rho * cos(phi);
    glm::vec3 cameraPos = glm::vec3(cam_x, cam_y, cam_z);

    glm::mat4 view = glm::lookAt(cameraPos, glm::vec3(0,0,0), glm::vec3(0,0,1));
    glm::mat4 projection = glm::perspective(glm::radians(50.0f), 1.0f, 0.1f, 1000.0f);

    return projection * view;
}
