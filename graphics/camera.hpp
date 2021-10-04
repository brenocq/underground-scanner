#ifndef __CAMERA
#define __CAMERA

#include <glm/glm.hpp>

class Camera
{
public:
    Camera();

    void zoom(float amount);
    void rotateDirection(float amount, bool axis); // 2D rotation

    glm::mat4 getViewProjectionMatrix();

private:
    float rho, phi, theta;
};

#endif
